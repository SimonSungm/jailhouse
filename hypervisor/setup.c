/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013-2017
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/processor.h>
#include <jailhouse/printk.h>
#include <jailhouse/entry.h>
#include <jailhouse/gcov.h>
#include <jailhouse/mmio.h>
#include <jailhouse/paging.h>
#include <jailhouse/control.h>
#include <jailhouse/string.h>
#include <jailhouse/unit.h>
#include <generated/version.h>
#include <asm/spinlock.h>

extern u8 __text_start[];

static const __attribute__((aligned(PAGE_SIZE))) u8 empty_page[PAGE_SIZE];

static spinlock_t init_lock;
static unsigned int master_cpu_id = INVALID_CPU_ID;
static volatile unsigned int entered_cpus, initialized_cpus;
static volatile int error;

static void init_early(unsigned int cpu_id)
{
	unsigned long core_and_percpu_size = hypervisor_header.core_size +
		sizeof(struct per_cpu) * hypervisor_header.max_cpus;
	u64 hyp_phys_start, hyp_phys_end;
	struct jailhouse_memory hv_page;

	master_cpu_id = cpu_id;

	system_config = (struct jailhouse_system *)					/* 计算config的虚拟地址 */
		(JAILHOUSE_BASE + core_and_percpu_size);

	virtual_console = SYS_FLAGS_VIRTUAL_DEBUG_CONSOLE(system_config->flags);

	arch_dbg_write_init();										/* x86:配置debug console的地址、操作和初始化debug console */
																/* ARM: 待补充 */
	printk("\nInitializing Jailhouse hypervisor %s on CPU %d\n",
	       JAILHOUSE_VERSION, cpu_id);
	printk("Code location: %p\n", __text_start);

	gcov_init();												/* 逐个调用__init_array_start开始的初始化函数，似乎里面并没有函数 */

	error = paging_init();										/* 初始化hypervisor页表，主要是映射hypervisor header、PERCPU区域以及MMIO */
	if (error)
		return;

	root_cell.config = &system_config->root_cell;				/* 拷贝root_cell的config到root cell的cell描述符中 */

	error = cell_init(&root_cell);								/* 初始化root cell的cell结构体，包括分配CPU的bitmap，初始化MMIO等 */
	if (error)
		return;

	error = arch_init_early();									/* x86: 初始化APIC，设置IDT，初始化VCPU */
	if (error)													/* 为guest parking page table创建映射，初始化初始化IO、TIMER、ept */
		return;													/* ARM: 待补充 */

	/*
	 * Back the region of the hypervisor core and per-CPU page with empty
	 * pages for Linux. This allows to fault-in the hypervisor region into
	 * Linux' page table before shutdown without triggering violations.
	 *
	 * Allow read access to the console page, if the hypervisor has the
	 * debug console flag JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE set.
	 */
	hyp_phys_start = system_config->hypervisor_memory.phys_start;
	hyp_phys_end = hyp_phys_start + system_config->hypervisor_memory.size;

	hv_page.virt_start = hyp_phys_start;
	hv_page.size = PAGE_SIZE;
	hv_page.flags = JAILHOUSE_MEM_READ;
	while (hv_page.virt_start < hyp_phys_end) {
		if (virtual_console &&
		    hv_page.virt_start == paging_hvirt2phys(&console))
			hv_page.phys_start = paging_hvirt2phys(&console);
		else
			hv_page.phys_start = paging_hvirt2phys(empty_page);
		error = arch_map_memory_region(&root_cell, &hv_page);			/* 将hypervisor的console映射到Linux的ept中 */
		if (error)
			return;
		hv_page.virt_start += PAGE_SIZE;
	}

	paging_dump_stats("after early setup");
	printk("Initializing processors:\n");
}

static void cpu_init(struct per_cpu *cpu_data)
{
	int err = -EINVAL;

	printk(" CPU %d... ", cpu_data->public.cpu_id);

	if (!cpu_id_valid(cpu_data->public.cpu_id))
		goto failed;

	cpu_data->public.cell = &root_cell;

	/* set up per-CPU page table */
	cpu_data->pg_structs.hv_paging = true;
	cpu_data->pg_structs.root_paging = hv_paging_structs.root_paging;
	cpu_data->pg_structs.root_table =							/* 初始化每个CPU自己的page table */
		(page_table_t)cpu_data->public.root_table_page;

	err = paging_create_hvpt_link(&cpu_data->pg_structs, JAILHOUSE_BASE);		/* 将hypervisor通过共享的页表映射到每个CPU的page table */
	if (err)
		goto failed;

	if (CON_IS_MMIO(system_config->debug_console.flags)) {
		err = paging_create_hvpt_link(&cpu_data->pg_structs,			/* 将debug console通过共享的页表映射到每个CPU的page table */
			(unsigned long)hypervisor_header.debug_console_base);
		if (err)
			goto failed;
	}

	/* set up private mapping of per-CPU data structure */
	err = paging_create(&cpu_data->pg_structs, paging_hvirt2phys(cpu_data),		/* 为每个CPU自己的cpu data区域做映射 */
			    sizeof(*cpu_data), LOCAL_CPU_BASE,
			    PAGE_DEFAULT_FLAGS,
			    PAGING_NON_COHERENT | PAGING_HUGE);
	if (err)
		goto failed;

	err = arch_cpu_init(cpu_data);				/* x86: 主要是保存Linux的现场和相关寄存器，切换到hypervisor的页表 */ 
	if (err)									/* 		初始化中断，并初始化VMCS结构体，进入VMXON模式 */
		goto failed;							/* ARM: 待补充 */

	/* Make sure any remappings to the temporary regions can be performed
	 * without allocations of page table pages. */
	err = paging_create(&cpu_data->pg_structs, 0,				/* 为临时映射分配内存，之后任何临时映射不需要在分配内存 */
			    NUM_TEMPORARY_PAGES * PAGE_SIZE,
			    TEMPORARY_MAPPING_BASE, PAGE_NONPRESENT_FLAGS,
			    PAGING_NON_COHERENT | PAGING_NO_HUGE);
	if (err)
		goto failed;

	printk("OK\n");

	/*
	 * If this CPU is last, make sure everything was committed before we
	 * signal the other CPUs spinning on initialized_cpus that they can
	 * continue.
	 */
	memory_barrier();
	initialized_cpus++;
	return;

failed:
	printk("FAILED\n");
	error = err;
}

static void init_late(void)
{
	unsigned int n, cpu, expected_cpus = 0;
	const struct jailhouse_memory *mem;
	struct unit *unit;

	for_each_cpu(cpu, root_cell.cpu_set)
		expected_cpus++;
	if (hypervisor_header.online_cpus != expected_cpus) {			/* 确保所有CPU正常工作 */
		error = trace_error(-EINVAL);
		return;
	}

	for_each_unit(unit) {									/* 为每个Unit做初始化,与具体硬件有关，包括IO相关设备等 */
		printk("Initializing unit: %s\n", unit->name);
		error = unit->init();
		if (error)
			return;
	}

	for_each_mem_region(mem, root_cell.config, n) {
		if (JAILHOUSE_MEMORY_IS_SUBPAGE(mem))		/* 判断是否是SUBPAGE，SUBPAGE的定义为非页对齐的区域或长度不为页的整数倍的区域 */
			error = mmio_subpage_register(&root_cell, mem);		/* SUBPAGE使用MMIO的subpage handler */
		else
			error = arch_map_memory_region(&root_cell, mem);	/* x86: 根据config中memory region的定义，做IOMMU和EPT的mapping */
		if (error)												/* ARM: 待补充 */
			return;
	}

	config_commit(&root_cell);			/* 使设置生效，例如清理cache中旧的vCPU相关内容，修改中断、IOMMU、PCI设置 */

	paging_dump_stats("after late setup");
}

/*
 * This is the architecture independent C entry point, which is called by
 * arch_entry. This routine is called on each CPU when initializing Jailhouse.
 */
int entry(unsigned int cpu_id, struct per_cpu *cpu_data)
{
	static volatile bool activate;
	bool master = false;

	cpu_data->public.cpu_id = cpu_id;

	spin_lock(&init_lock);

	/*
	 * If this CPU is last, make sure everything was committed before we
	 * signal the other CPUs spinning on entered_cpus that they can
	 * continue.
	 */
	memory_barrier();
	entered_cpus++;

	spin_unlock(&init_lock);

	while (entered_cpus < hypervisor_header.online_cpus)			/* 等待所有CPU都进入Hypervisor */
		cpu_relax();

	spin_lock(&init_lock);

	if (master_cpu_id == INVALID_CPU_ID) {							/* 令master CPU做全局的初始化工作，其余CPU则直接进行自己的初始化 */
		/* Only the master CPU, the first to enter this
		 * function, performs system-wide initializations. */
		master = true;
		init_early(cpu_id);											/* x86: 映射debug console、调用初始化函数列表中的函数,对hypervisor、 */
	}																/* PER CPU区域、MMIO做页表映射，初始化APIC，IDT，初始化Linux的VCPU、EPT等 */
																	/* ARM: 待补充 */
	if (!error)
		cpu_init(cpu_data);											/* x86: 保存Linux系统寄存器的情况，切换到Hypervisor页表，初始化VMCS等 */
																	/* ARM: 待补充 */
	spin_unlock(&init_lock);

	while (!error && initialized_cpus < hypervisor_header.online_cpus)		/* 等待所有CPU初始化完成 */
		cpu_relax();					

	if (!error && master) {											/* 令master CPU做全局初始化工作 */
		init_late();											/* x86: 初始化各个硬件UNIT，做MMIO映射，根据config中的memory region做IOMMU和EPT的映射等 */
		if (!error) {											/* ARM: 待补充 */
			/*
			 * Make sure everything was committed before we signal
			 * the other CPUs that they can continue.
			 */
			memory_barrier();
			activate = true;
		}
	} else {
		while (!error && !activate)									/* 等待master CPU完成初始化 */
			cpu_relax();
	}

	if (error) {
		if (master)								/* master CPU出错则导致hypervisor关闭 */
			shutdown();							/* CPU无关的关闭操作，包括中断、IOMMU等 */
		arch_cpu_restore(cpu_id, error);		/* 恢复Linux的上下文 */
		return error;
	}

	if (master)
		printk("Activating hypervisor\n");

	/* point of no return */
	arch_cpu_activate_vmm();									/* 进入VM执行,将Linux变成Guest OS, Linux的控制流从enter_hypervisor的entry(cpu)开始执行*/
}

/** Hypervisor description header. */
struct jailhouse_header __attribute__((section(".header")))
hypervisor_header = {
	.signature = JAILHOUSE_SIGNATURE,
	.core_size = (unsigned long)__page_pool - JAILHOUSE_BASE,
	.percpu_size = sizeof(struct per_cpu),
	.entry = arch_entry - JAILHOUSE_BASE,
	.console_page = (unsigned long)&console - JAILHOUSE_BASE,
};
