/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2014-2017
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Alternatively, you can use or redistribute this file under the following
 * BSD license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Configuration for Inspur NF5270M5
 * created with './jailhouse config create sysconfig.c'
 *
 * NOTE: This config expects the following to be appended to your kernel cmdline
 *       "memmap=0x5200000$0x3a000000"
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[106];
	struct jailhouse_irqchip irqchips[9];
	struct jailhouse_pio pio_regions[44];
	struct jailhouse_pci_device pci_devices[211];
	struct jailhouse_pci_capability pci_caps[86];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0x3a000000,
			.size = 0x4000000,
		},
		.debug_console = {
			.address = 0x3f8,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO |
				 JAILHOUSE_CON_REGDIST_1,
		},
		.platform_info = {
			.pci_mmconfig_base = 0x80000000,
			.pci_mmconfig_end_bus = 0xff,
			.iommu_units = {
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xd37fc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xe0ffc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xee7fc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xfbffc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xaaffc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xb87fc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xc5ffc000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0x9d7fc000,
					.size = 0x1000,
				},
			},
			.x86 = {
				.pm_timer_address = 0x508,
				.vtd_interrupt_limit = 1024,
			},
		},
		.root_cell = {
			.name = "RootCell",
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.num_pio_regions = ARRAY_SIZE(config.pio_regions),
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),
			.num_pci_caps = ARRAY_SIZE(config.pci_caps),
		},
	},

	.cpus = {
		0x000000ffffffffff,
	},

	.mem_regions = {
		/* MemRegion: 00000000-0009ffff : System RAM */
		{
			.phys_start = 0x0,
			.virt_start = 0x0,
			.size = 0xf0000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 000f0000-000fffff : System ROM */
		{
			.phys_start = 0xf0000,
			.virt_start = 0xf0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 00100000-39ffffff : System RAM */
		{
			.phys_start = 0x100000,
			.virt_start = 0x100000,
			.size = 0x39f00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 3f200000-5f5d5fff : System RAM */
		{
			.phys_start = 0x3f200000,
			.virt_start = 0x3f200000,
			.size = 0x203d6000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 5f5d6000-5f80cfff : ACPI Non-volatile Storage */
		{
			.phys_start = 0x5f5d6000,
			.virt_start = 0x5f5d6000,
			.size = 0x237000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 5f80d000-626e9fff : System RAM */
		{
			.phys_start = 0x5f80d000,
			.virt_start = 0x5f80d000,
			.size = 0x2fac000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 627b9000-659bcfff : System RAM */
		{
			.phys_start = 0x627b9000,
			.virt_start = 0x627b9000,
			.size = 0x3204000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 659be000-67a1cfff : System RAM */
		{
			.phys_start = 0x659be000,
			.virt_start = 0x659be000,
			.size = 0x3950000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 6930e018-6930e018 : APEI ERST */
		{
			.phys_start = 0x6930e000,
			.virt_start = 0x6930e000,
			.size = 0x1020000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6a32e000-6a68dfff : System RAM */
		{
			.phys_start = 0x6a32e000,
			.virt_start = 0x6a32e000,
			.size = 0x360000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 6a68e000-6b3fbfff : ACPI Non-volatile Storage */
		{
			.phys_start = 0x6a68e000,
			.virt_start = 0x6a68e000,
			.size = 0x313c000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 6d7ca000-6fffffff : System RAM */
		{
			.phys_start = 0x6d7ca000,
			.virt_start = 0x6d7ca000,
			.size = 0x2a836000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 98000000-9bffffff : 0000:02:00.0 */
		{
			.phys_start = 0x98000000,
			.virt_start = 0x98000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c000000-9c01ffff : 0000:02:00.0 */
		{
			.phys_start = 0x9c000000,
			.virt_start = 0x9c000000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c100000-9c17ffff : ahci */
		{
			.phys_start = 0x9c100000,
			.virt_start = 0x9c100000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c180000-9c1fffff : ahci */
		{
			.phys_start = 0x9c180000,
			.virt_start = 0x9c180000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c200000-9c203fff : 0000:00:1f.2 */
		{
			.phys_start = 0x9c200000,
			.virt_start = 0x9c200000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c204000-9c205fff : ahci */
		{
			.phys_start = 0x9c204000,
			.virt_start = 0x9c204000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c206000-9c207fff : ahci */
		{
			.phys_start = 0x9c206000,
			.virt_start = 0x9c206000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c208000-9c2080ff : ahci */
		{
			.phys_start = 0x9c208000,
			.virt_start = 0x9c208000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c209000-9c2090ff : ahci */
		{
			.phys_start = 0x9c209000,
			.virt_start = 0x9c209000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 9c20a000-9c20afff : 0000:00:05.4 */
		{
			.phys_start = 0x9c20a000,
			.virt_start = 0x9c20a000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: aac00000-aacfffff : 0000:18:00.0 */
		{
			.phys_start = 0xaac00000,
			.virt_start = 0xaac00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: aad00000-aad7ffff : 0000:1a:00.1 */
		{
			.phys_start = 0xaad00000,
			.virt_start = 0xaad00000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: aad80000-aadfffff : 0000:1a:00.0 */
		{
			.phys_start = 0xaad80000,
			.virt_start = 0xaad80000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: aae00000-aae1ffff : 0000:18:00.0 */
		{
			.phys_start = 0xaae00000,
			.virt_start = 0xaae00000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: aaf00000-aaf00fff : 0000:17:05.4 */
		{
			.phys_start = 0xaaf00000,
			.virt_start = 0xaaf00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: b8700000-b8700fff : 0000:3a:05.4 */
		{
			.phys_start = 0xb8700000,
			.virt_start = 0xb8700000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: c5d00000-c5dfffff : 0000:5e:00.0 */
		{
			.phys_start = 0xc5d00000,
			.virt_start = 0xc5d00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: c5e00000-c5e3ffff : mpt3sas */
		{
			.phys_start = 0xc5e00000,
			.virt_start = 0xc5e00000,
			.size = 0x40000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: c5e40000-c5e4dfff : mpt3sas */
		{
			.phys_start = 0xc5e40000,
			.virt_start = 0xc5e40000,
			.size = 0xe000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: c5e4f000-c5e4ffff : mpt3sas */
		{
			.phys_start = 0xc5e4f000,
			.virt_start = 0xc5e4f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: c5f00000-c5f00fff : 0000:5d:05.4 */
		{
			.phys_start = 0xc5f00000,
			.virt_start = 0xc5f00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: d3700000-d3700fff : 0000:80:05.4 */
		{
			.phys_start = 0xd3700000,
			.virt_start = 0xd3700000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: e0f00000-e0f00fff : 0000:85:05.4 */
		{
			.phys_start = 0xe0f00000,
			.virt_start = 0xe0f00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: ee700000-ee700fff : 0000:ae:05.4 */
		{
			.phys_start = 0xee700000,
			.virt_start = 0xee700000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fbf00000-fbf00fff : 0000:d7:05.4 */
		{
			.phys_start = 0xfbf00000,
			.virt_start = 0xfbf00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd000000-fdabffff : pnp 00:04 */
		{
			.phys_start = 0xfd000000,
			.virt_start = 0xfd000000,
			.size = 0xac0000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdad0000-fdadffff : pnp 00:04 */
		{
			.phys_start = 0xfdad0000,
			.virt_start = 0xfdad0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdc6000c-fdc6000f : iTCO_wdt */
		{
			.phys_start = 0xfdc6000c,
			.virt_start = 0xfdc6000c,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe000000-fe00ffff : pnp 00:04 */
		{
			.phys_start = 0xfe000000,
			.virt_start = 0xfe000000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe010000-fe010fff : 0000:00:1f.5 */
		{
			.phys_start = 0xfe010000,
			.virt_start = 0xfe010000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe011000-fe01ffff : pnp 00:04 */
		{
			.phys_start = 0xfe011000,
			.virt_start = 0xfe011000,
			.size = 0xf000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe036000-fe03bfff : pnp 00:04 */
		{
			.phys_start = 0xfe036000,
			.virt_start = 0xfe036000,
			.size = 0x6000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe03d000-fe3fffff : pnp 00:04 */
		{
			.phys_start = 0xfe03d000,
			.virt_start = 0xfe03d000,
			.size = 0x3c3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe410000-fe7fffff : pnp 00:04 */
		{
			.phys_start = 0xfe410000,
			.virt_start = 0xfe410000,
			.size = 0x3f0000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed00000-fed003ff : PNP0103:00 */
		{
			.phys_start = 0xfed00000,
			.virt_start = 0xfed00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed12000-fed1200f : pnp 00:01 */
		{
			.phys_start = 0xfed12000,
			.virt_start = 0xfed12000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed1b000-fed1bfff : pnp 00:01 */
		{
			.phys_start = 0xfed1b000,
			.virt_start = 0xfed1b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed45000-fed8bfff : pnp 00:01 */
		{
			.phys_start = 0xfed45000,
			.virt_start = 0xfed45000,
			.size = 0x47000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fee00000-feefffff : pnp 00:01 */
		{
			.phys_start = 0xfee00000,
			.virt_start = 0xfee00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: ff000000-ffffffff : pnp 00:01 */
		{
			.phys_start = 0xff000000,
			.virt_start = 0xff000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 100000000-407fffffff : System RAM */
		{
			.phys_start = 0x100000000,
			.virt_start = 0x100000000,
			.size = 0x3f80000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 380000000000-3800000000ff : 0000:00:1f.4 */
		{
			.phys_start = 0x380000000000,
			.virt_start = 0x380000000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff00000-38fffff0ffff : xhci-hcd */
		{
			.phys_start = 0x38fffff00000,
			.virt_start = 0x38fffff00000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff10000-38fffff11fff : ioatdma */
		{
			.phys_start = 0x38fffff10000,
			.virt_start = 0x38fffff10000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff13000-38fffff13fff : ioatdma */
		{
			.phys_start = 0x38fffff13000,
			.virt_start = 0x38fffff13000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff14000-38fffff15fff : ioatdma */
		{
			.phys_start = 0x38fffff14000,
			.virt_start = 0x38fffff14000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff17000-38fffff17fff : ioatdma */
		{
			.phys_start = 0x38fffff17000,
			.virt_start = 0x38fffff17000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff18000-38fffff19fff : ioatdma */
		{
			.phys_start = 0x38fffff18000,
			.virt_start = 0x38fffff18000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff1b000-38fffff1bfff : ioatdma */
		{
			.phys_start = 0x38fffff1b000,
			.virt_start = 0x38fffff1b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff1c000-38fffff1dfff : ioatdma */
		{
			.phys_start = 0x38fffff1c000,
			.virt_start = 0x38fffff1c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff1f000-38fffff1ffff : ioatdma */
		{
			.phys_start = 0x38fffff1f000,
			.virt_start = 0x38fffff1f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff20000-38fffff21fff : ioatdma */
		{
			.phys_start = 0x38fffff20000,
			.virt_start = 0x38fffff20000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff23000-38fffff23fff : ioatdma */
		{
			.phys_start = 0x38fffff23000,
			.virt_start = 0x38fffff23000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff24000-38fffff25fff : ioatdma */
		{
			.phys_start = 0x38fffff24000,
			.virt_start = 0x38fffff24000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff27000-38fffff27fff : ioatdma */
		{
			.phys_start = 0x38fffff27000,
			.virt_start = 0x38fffff27000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff28000-38fffff29fff : ioatdma */
		{
			.phys_start = 0x38fffff28000,
			.virt_start = 0x38fffff28000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff2b000-38fffff2bfff : ioatdma */
		{
			.phys_start = 0x38fffff2b000,
			.virt_start = 0x38fffff2b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff2c000-38fffff2dfff : ioatdma */
		{
			.phys_start = 0x38fffff2c000,
			.virt_start = 0x38fffff2c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff2f000-38fffff2ffff : ioatdma */
		{
			.phys_start = 0x38fffff2f000,
			.virt_start = 0x38fffff2f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff30000-38fffff30fff : 0000:00:16.4 */
		{
			.phys_start = 0x38fffff30000,
			.virt_start = 0x38fffff30000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff31000-38fffff31fff : 0000:00:16.1 */
		{
			.phys_start = 0x38fffff31000,
			.virt_start = 0x38fffff31000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff32000-38fffff32fff : mei_me */
		{
			.phys_start = 0x38fffff32000,
			.virt_start = 0x38fffff32000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 38fffff33000-38fffff33fff : 0000:00:14.2 */
		{
			.phys_start = 0x38fffff33000,
			.virt_start = 0x38fffff33000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39fffd000000-39fffdffffff : i40e */
		{
			.phys_start = 0x39fffd000000,
			.virt_start = 0x39fffd000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39fffe000000-39fffeffffff : i40e */
		{
			.phys_start = 0x39fffe000000,
			.virt_start = 0x39fffe000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff000000-39ffff3fffff : 0000:1a:00.1 */
		{
			.phys_start = 0x39ffff000000,
			.virt_start = 0x39ffff000000,
			.size = 0x400000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff400000-39ffff7fffff : 0000:1a:00.0 */
		{
			.phys_start = 0x39ffff400000,
			.virt_start = 0x39ffff400000,
			.size = 0x400000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff801000-39ffff807fff : i40e */
		{
			.phys_start = 0x39ffff801000,
			.virt_start = 0x39ffff801000,
			.size = 0x7000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff809000-39ffff80ffff : i40e */
		{
			.phys_start = 0x39ffff809000,
			.virt_start = 0x39ffff809000,
			.size = 0x7000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff810000-39ffff88ffff : 0000:1a:00.1 */
		{
			.phys_start = 0x39ffff810000,
			.virt_start = 0x39ffff810000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 39ffff890000-39ffff90ffff : 0000:1a:00.0 */
		{
			.phys_start = 0x39ffff890000,
			.virt_start = 0x39ffff890000,
			.size = 0x80000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff00000-3cfffff01fff : ioatdma */
		{
			.phys_start = 0x3cfffff00000,
			.virt_start = 0x3cfffff00000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff03000-3cfffff03fff : ioatdma */
		{
			.phys_start = 0x3cfffff03000,
			.virt_start = 0x3cfffff03000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff04000-3cfffff05fff : ioatdma */
		{
			.phys_start = 0x3cfffff04000,
			.virt_start = 0x3cfffff04000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff07000-3cfffff07fff : ioatdma */
		{
			.phys_start = 0x3cfffff07000,
			.virt_start = 0x3cfffff07000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff08000-3cfffff09fff : ioatdma */
		{
			.phys_start = 0x3cfffff08000,
			.virt_start = 0x3cfffff08000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff0b000-3cfffff0bfff : ioatdma */
		{
			.phys_start = 0x3cfffff0b000,
			.virt_start = 0x3cfffff0b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff0c000-3cfffff0dfff : ioatdma */
		{
			.phys_start = 0x3cfffff0c000,
			.virt_start = 0x3cfffff0c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff0f000-3cfffff0ffff : ioatdma */
		{
			.phys_start = 0x3cfffff0f000,
			.virt_start = 0x3cfffff0f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff10000-3cfffff11fff : ioatdma */
		{
			.phys_start = 0x3cfffff10000,
			.virt_start = 0x3cfffff10000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff13000-3cfffff13fff : ioatdma */
		{
			.phys_start = 0x3cfffff13000,
			.virt_start = 0x3cfffff13000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff14000-3cfffff15fff : ioatdma */
		{
			.phys_start = 0x3cfffff14000,
			.virt_start = 0x3cfffff14000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff17000-3cfffff17fff : ioatdma */
		{
			.phys_start = 0x3cfffff17000,
			.virt_start = 0x3cfffff17000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff18000-3cfffff19fff : ioatdma */
		{
			.phys_start = 0x3cfffff18000,
			.virt_start = 0x3cfffff18000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff1b000-3cfffff1bfff : ioatdma */
		{
			.phys_start = 0x3cfffff1b000,
			.virt_start = 0x3cfffff1b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff1c000-3cfffff1dfff : ioatdma */
		{
			.phys_start = 0x3cfffff1c000,
			.virt_start = 0x3cfffff1c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 3cfffff1f000-3cfffff1ffff : ioatdma */
		{
			.phys_start = 0x3cfffff1f000,
			.virt_start = 0x3cfffff1f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6d2c1000-6d2d1fff : ACPI DMAR RMRR */
		/* PCI device: 00:14.0 */
		{
			.phys_start = 0x6d2c1000,
			.virt_start = 0x6d2c1000,
			.size = 0x11000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 3a600000-3f1fffff : JAILHOUSE Inmate Memory */
		{
			.phys_start = 0x3e000000,
			.virt_start = 0x3e000000,
			.size = 0x1200000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* IOAPIC 8, GSI base 0 */
		{
			.address = 0xfec00000,
			.id = 0x7f0f8,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 9, GSI base 24 */
		{
			.address = 0xfec01000,
			.id = 0x7002c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 10, GSI base 32 */
		{
			.address = 0xfec08000,
			.id = 0x4172c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 11, GSI base 40 */
		{
			.address = 0xfec10000,
			.id = 0x53a2c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 12, GSI base 48 */
		{
			.address = 0xfec18000,
			.id = 0x65d2c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 15, GSI base 72 */
		{
			.address = 0xfec20000,
			.id = 0x802c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 16, GSI base 80 */
		{
			.address = 0xfec28000,
			.id = 0x1852c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 17, GSI base 88 */
		{
			.address = 0xfec30000,
			.id = 0x2ae2c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* IOAPIC 18, GSI base 96 */
		{
			.address = 0xfec38000,
			.id = 0x3d72c,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
	},

	.pio_regions = {
		/* Port I/O: 0000-001f : dma1 */
		/* PIO_RANGE(0x0, 0x20), */
		PIO_RANGE(0x0, 0x20),
		/* Port I/O: 0020-0021 : pic1 */
		/* PIO_RANGE(0x20, 0x2), */
		PIO_RANGE(0x20, 0x2),
		/* Port I/O: 0040-0043 : timer0 */
		PIO_RANGE(0x40, 0x4),
		/* Port I/O: 0050-0053 : timer1 */
		/* PIO_RANGE(0x50, 0x4), */
		PIO_RANGE(0x50, 0x4),
		/* Port I/O: 0060-0060 : keyboard */
		PIO_RANGE(0x60, 0x1),
		/* Port I/O: 0061-0061 : PNP0800:00 */
		PIO_RANGE(0x61, 0x1),
		/* Port I/O: 0064-0064 : keyboard */
		PIO_RANGE(0x64, 0x1),
		/* Port I/O: 0070-0071 : rtc0 */
		PIO_RANGE(0x70, 0x2),
		/* Port I/O: 0080-008f : dma page reg */
		/* PIO_RANGE(0x80, 0x10), */
		PIO_RANGE(0x80, 0x10),
		/* Port I/O: 00a0-00a1 : pic2 */
		/* PIO_RANGE(0xa0, 0x2), */
		PIO_RANGE(0xa0, 0x2),
		/* Port I/O: 00b2-00b2 : APEI ERST */
		/* PIO_RANGE(0xb2, 0x1), */
		PIO_RANGE(0xb2, 0xe),
		/* Port I/O: 00c0-00df : dma2 */
		/* PIO_RANGE(0xc0, 0x20), */
		PIO_RANGE(0xc0, 0x20),
		/* Port I/O: 00f0-00f0 : PNP0C04:00 */
		/* PIO_RANGE(0xf0, 0x1), */
		PIO_RANGE(0xf0, 0x1),
		/* Port I/O: 02f8-02ff : serial */
		PIO_RANGE(0x2f8, 0x8),
		/* Port I/O: 03b0-03bb : PCI Bus 0000:00 */
		/* PIO_RANGE(0x3b0, 0xc), */
		PIO_RANGE(0x3b0, 0xc),
		/* Port I/O: 03c0-03df : PCI Bus 0000:00 */
		/* PIO_RANGE(0x3c0, 0x20), */
		PIO_RANGE(0x3c0, 0x20),
		/* Port I/O: 03f8-03ff : serial */
		PIO_RANGE(0x3f8, 0x8),
		/* Port I/O: 0400-041f : iTCO_wdt */
		/* PIO_RANGE(0x400, 0x20), */
		PIO_RANGE(0x400, 0x20),
		/* Port I/O: 0500-0503 : ACPI PM1a_EVT_BLK */
		/* PIO_RANGE(0x500, 0x4), */
		PIO_RANGE(0x500, 0x4),
		/* Port I/O: 0504-0505 : ACPI PM1a_CNT_BLK */
		/* PIO_RANGE(0x504, 0x2), */
		PIO_RANGE(0x504, 0x2),
		/* Port I/O: 0508-050b : ACPI PM_TMR */
		/* PIO_RANGE(0x508, 0x4), */
		PIO_RANGE(0x508, 0x48),
		/* Port I/O: 0550-0550 : ACPI PM2_CNT_BLK */
		/* PIO_RANGE(0x550, 0x1), */
		PIO_RANGE(0x550, 0x1),
		/* Port I/O: 0580-059f : ACPI GPE0_BLK */
		/* PIO_RANGE(0x580, 0x20), */
		PIO_RANGE(0x580, 0x20),
		/* Port I/O: 0600-061f : pnp 00:01 */
		/* PIO_RANGE(0x600, 0x20), */
		PIO_RANGE(0x600, 0x20),
		/* Port I/O: 0780-079f : i801_smbus */
		/* PIO_RANGE(0x780, 0x20), */
		PIO_RANGE(0x780, 0x20),
		/* Port I/O: 0800-081f : pnp 00:01 */
		/* PIO_RANGE(0x800, 0x20), */
		PIO_RANGE(0x800, 0x20),
		/* Port I/O: 0880-0883 : pnp 00:01 */
		/* PIO_RANGE(0x880, 0x4), */
		PIO_RANGE(0x880, 0x4),
		/* Port I/O: 0a00-0a0f : pnp 00:02 */
		/* PIO_RANGE(0xa00, 0x10), */
		PIO_RANGE(0xa00, 0x10),
		/* Port I/O: 0a10-0a1f : pnp 00:02 */
		/* PIO_RANGE(0xa10, 0x10), */
		PIO_RANGE(0xa10, 0x10),
		/* Port I/O: 0a20-0a2f : pnp 00:02 */
		/* PIO_RANGE(0xa20, 0x10), */
		PIO_RANGE(0xa20, 0x10),
		/* Port I/O: 0a30-0a3f : pnp 00:02 */
		/* PIO_RANGE(0xa30, 0x10), */
		PIO_RANGE(0xa30, 0x10),
		/* Port I/O: 0a40-0a4f : pnp 00:02 */
		/* PIO_RANGE(0xa40, 0x10), */
		PIO_RANGE(0xa40, 0x10),
		/* Port I/O: 0ca2-0ca2 : ipmi_si */
		/* PIO_RANGE(0xca2, 0x1), */
		PIO_RANGE(0xca2, 0x1),
		/* Port I/O: 0ca3-0ca3 : ipmi_si */
		/* PIO_RANGE(0xca3, 0x1), */
		PIO_RANGE(0xca3, 0x1),
		PIO_RANGE(0x1000, 0x1000),
		/* Port I/O: 2000-207f : 0000:02:00.0 */
		PIO_RANGE(0x2000, 0x80),
		PIO_RANGE(0x2400, 0x4),
		/* Port I/O: 3000-301f : 0000:00:17.0 */
		PIO_RANGE(0x3000, 0x20),
		/* Port I/O: 3020-303f : 0000:00:11.5 */
		PIO_RANGE(0x3020, 0x20),
		/* Port I/O: 3040-3043 : 0000:00:17.0 */
		PIO_RANGE(0x3040, 0x4),
		/* Port I/O: 3050-3057 : 0000:00:17.0 */
		PIO_RANGE(0x3050, 0x8),
		/* Port I/O: 3060-3063 : 0000:00:11.5 */
		PIO_RANGE(0x3060, 0x4),
		/* Port I/O: 3070-3077 : 0000:00:11.5 */
		PIO_RANGE(0x3070, 0x5f90),
		/* Port I/O: 9000-90ff : 0000:5e:00.0 */
		PIO_RANGE(0x9000, 0x7000),
	},

	.pci_devices = {
		/* PCIDevice: 00:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 8,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:04.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x20,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff2e000,
		},
		/* PCIDevice: 00:04.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x21,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff2a000,
		},
		/* PCIDevice: 00:04.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x22,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff26000,
		},
		/* PCIDevice: 00:04.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x23,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff22000,
		},
		/* PCIDevice: 00:04.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x24,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff1e000,
		},
		/* PCIDevice: 00:04.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x25,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff1a000,
		},
		/* PCIDevice: 00:04.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x26,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff16000,
		},
		/* PCIDevice: 00:04.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x27,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x38fffff12000,
		},
		/* PCIDevice: 00:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x28,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x2a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x2c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x40,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:08.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x41,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:08.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x42,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:11.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x88,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 17,
			.num_caps = 1,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:11.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x89,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 17,
			.num_caps = 1,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:11.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8d,
			.bar_mask = {
				0xffffe000, 0xffffff00, 0xfffffff8,
				0xfffffffc, 0xffffffe0, 0xfff80000,
			},
			.caps_start = 18,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xa0,
			.bar_mask = {
				0xffff0000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 21,
			.num_caps = 2,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xa2,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 23,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xb0,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 25,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xb1,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 25,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xb4,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 25,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:17.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xb8,
			.bar_mask = {
				0xffffe000, 0xffffff00, 0xfffffff8,
				0xfffffffc, 0xffffffe0, 0xfff80000,
			},
			.caps_start = 18,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xe0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 27,
			.num_caps = 7,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xe5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 27,
			.num_caps = 7,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xf8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xfa,
			.bar_mask = {
				0xffffc000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xfc,
			.bar_mask = {
				0xffffff00, 0xffffffff, 0x00000000,
				0x00000000, 0xffffffe0, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xfd,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 01:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x100,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 34,
			.num_caps = 6,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 02:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x200,
			.bar_mask = {
				0xfc000000, 0xfffe0000, 0xffffff80,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 40,
			.num_caps = 2,
			.num_msi_vectors = 2,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1700,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 42,
			.num_caps = 11,
			.num_msi_vectors = 2,
			.msi_64bits = 0,
			.msi_maskable = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1728,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x172a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x172c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1740,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1741,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1742,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1743,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1744,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1745,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1746,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:08.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1747,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:09.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1748,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:09.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1749,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1770,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1771,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1772,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1773,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1774,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1775,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1776,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0e.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1777,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1778,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:0f.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x1779,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1d.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17e8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1d.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17e9,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1d.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17ea,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1d.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17eb,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f1,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f2,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f3,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f4,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 17:1e.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x17f6,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 18:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 4,
			.domain = 0x0,
			.bdf = 0x1800,
			.bar_mask = {
				0xfffe0000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 53,
			.num_caps = 5,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 19:03.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 4,
			.domain = 0x0,
			.bdf = 0x1918,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 58,
			.num_caps = 5,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 1a:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 4,
			.domain = 0x0,
			.bdf = 0x1a00,
			.bar_mask = {
				0xff000000, 0xffffffff, 0x00000000,
				0xffff8000, 0xffffffff, 0x00000000,
			},
			.caps_start = 63,
			.num_caps = 10,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 1,
			.num_msix_vectors = 129,
			.msix_region_size = 0x1000,
			.msix_address = 0x39ffff808000,
		},
		/* PCIDevice: 1a:00.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 4,
			.domain = 0x0,
			.bdf = 0x1a01,
			.bar_mask = {
				0xff000000, 0xffffffff, 0x00000000,
				0xffff8000, 0xffffffff, 0x00000000,
			},
			.caps_start = 63,
			.num_caps = 10,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 1,
			.num_msix_vectors = 129,
			.msix_region_size = 0x1000,
			.msix_address = 0x39ffff800000,
		},
		/* PCIDevice: 3a:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a28,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a2a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a2c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a40,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:09.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a48,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a50,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a51,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a52,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a53,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a54,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a55,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a56,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0a.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a57,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0b.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a58,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0b.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a59,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0b.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a5a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0b.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a5b,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a60,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a61,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a62,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a63,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a64,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a65,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a66,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0c.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a67,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0d.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a68,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0d.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a69,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0d.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a6a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 3a:0d.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x3a6b,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d00,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 42,
			.num_caps = 11,
			.num_msi_vectors = 2,
			.msi_64bits = 0,
			.msi_maskable = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d28,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d2a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d2c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:0e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d70,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:0e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d71,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 75,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:0f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d78,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:0f.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d79,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 75,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:12.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d90,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:12.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d91,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:12.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5d92,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:15.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5da8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:15.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5da9,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:16.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5db0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:16.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5db1,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:16.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5db4,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5d:16.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x5db5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 5e:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 6,
			.domain = 0x0,
			.bdf = 0x5e00,
			.bar_mask = {
				0xffffff00, 0xffff0000, 0xffffffff,
				0xfffc0000, 0xffffffff, 0x00000000,
			},
			.caps_start = 77,
			.num_caps = 9,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 1,
			.num_msix_vectors = 96,
			.msix_region_size = 0x1000,
			.msix_address = 0xc5e4e000,
		},
		/* PCIDevice: 80:04.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8020,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff1e000,
		},
		/* PCIDevice: 80:04.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8021,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff1a000,
		},
		/* PCIDevice: 80:04.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8022,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff16000,
		},
		/* PCIDevice: 80:04.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8023,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff12000,
		},
		/* PCIDevice: 80:04.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8024,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff0e000,
		},
		/* PCIDevice: 80:04.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8025,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff0a000,
		},
		/* PCIDevice: 80:04.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8026,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff06000,
		},
		/* PCIDevice: 80:04.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x8027,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 4,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 1,
			.msix_region_size = 0x1000,
			.msix_address = 0x3cfffff02000,
		},
		/* PCIDevice: 80:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8028,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 80:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x802a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 80:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x802c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 80:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8040,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 80:08.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8041,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 80:08.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8042,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8528,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x852a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x852c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8540,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8541,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8542,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8543,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8544,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8545,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8546,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:08.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8547,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:09.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8548,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:09.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8549,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8570,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8571,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8572,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8573,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8574,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8575,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8576,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0e.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8577,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8578,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:0f.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x8579,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1d.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85e8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1d.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85e9,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1d.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85ea,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1d.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85eb,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f1,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f2,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f3,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f4,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 85:1e.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0x85f6,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae28,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae2a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae2c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae40,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:09.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae48,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae50,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae51,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae52,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae53,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae54,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae55,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae56,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0a.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae57,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0b.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae58,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0b.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae59,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0b.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae5a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0b.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae5b,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae60,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae61,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae62,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae63,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae64,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae65,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae66,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0c.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae67,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0d.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae68,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0d.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae69,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0d.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae6a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: ae:0d.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xae6b,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 73,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:05.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd728,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:05.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd72a,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:05.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd72c,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 3,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:0e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd770,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:0e.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd771,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 75,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:0f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd778,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:0f.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd779,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 75,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:12.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd790,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 12,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:12.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd791,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:12.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd792,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:15.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7a8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:15.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7a9,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:16.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7b0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:16.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7b1,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:16.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7b4,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: d7:16.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 7,
			.domain = 0x0,
			.bdf = 0xd7b5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
	},

	.pci_caps = {
		/* PCIDevice: 00:00.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x90,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xe0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x144,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1d0,
			.len = 0xe,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x250,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x280,
			.len = 0x1c,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x300,
			.len = 0x3c,
			.flags = 0,
		},
		/* PCIDevice: 00:04.0 */
		/* PCIDevice: 00:04.1 */
		/* PCIDevice: 00:04.2 */
		/* PCIDevice: 00:04.3 */
		/* PCIDevice: 00:04.4 */
		/* PCIDevice: 00:04.5 */
		/* PCIDevice: 00:04.6 */
		/* PCIDevice: 00:04.7 */
		/* PCIDevice: 80:04.0 */
		/* PCIDevice: 80:04.1 */
		/* PCIDevice: 80:04.2 */
		/* PCIDevice: 80:04.3 */
		/* PCIDevice: 80:04.4 */
		/* PCIDevice: 80:04.5 */
		/* PCIDevice: 80:04.6 */
		/* PCIDevice: 80:04.7 */
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0x80,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x90,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xe0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x0 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 00:05.0 */
		/* PCIDevice: 00:05.2 */
		/* PCIDevice: 00:08.0 */
		/* PCIDevice: 00:08.2 */
		/* PCIDevice: 17:05.0 */
		/* PCIDevice: 17:05.2 */
		/* PCIDevice: 3a:05.0 */
		/* PCIDevice: 3a:05.2 */
		/* PCIDevice: 5d:05.0 */
		/* PCIDevice: 5d:05.2 */
		/* PCIDevice: 5d:0e.0 */
		/* PCIDevice: 5d:0f.0 */
		/* PCIDevice: 5d:12.0 */
		/* PCIDevice: 80:05.0 */
		/* PCIDevice: 80:05.2 */
		/* PCIDevice: 80:08.0 */
		/* PCIDevice: 80:08.2 */
		/* PCIDevice: 85:05.0 */
		/* PCIDevice: 85:05.2 */
		/* PCIDevice: ae:05.0 */
		/* PCIDevice: ae:05.2 */
		/* PCIDevice: d7:05.0 */
		/* PCIDevice: d7:05.2 */
		/* PCIDevice: d7:0e.0 */
		/* PCIDevice: d7:0f.0 */
		/* PCIDevice: d7:12.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = 0x0 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 00:05.4 */
		/* PCIDevice: 17:05.4 */
		/* PCIDevice: 3a:05.4 */
		/* PCIDevice: 5d:05.4 */
		/* PCIDevice: 80:05.4 */
		/* PCIDevice: 85:05.4 */
		/* PCIDevice: ae:05.4 */
		/* PCIDevice: d7:05.4 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x44,
			.len = 0x14,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xe0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x0 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 00:11.0 */
		/* PCIDevice: 00:11.1 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x80,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:11.5 */
		/* PCIDevice: 00:17.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xa,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x70,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SATA,
			.start = 0xa8,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x70,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:14.2 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x50,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xa,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:16.0 */
		/* PCIDevice: 00:16.1 */
		/* PCIDevice: 00:16.4 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x50,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x8c,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:1c.0 */
		/* PCIDevice: 00:1c.5 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xa,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0x90,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xa0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ACS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x140,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x220,
			.len = 0x10,
			.flags = 0,
		},
		/* PCIDevice: 01:00.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x78,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0xc0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x800,
			.len = 0x40,
			.flags = 0,
		},
		/* PCIDevice: 02:00.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x40,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 17:00.0 */
		/* PCIDevice: 5d:00.0 */
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0x40,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x60,
			.len = 0x14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x90,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xe0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ACS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x110,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x148,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1d0,
			.len = 0xe,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x250,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x280,
			.len = 0x1c,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x300,
			.len = 0x3c,
			.flags = 0,
		},
		/* PCIDevice: 18:00.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x80,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0x88,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 0x10,
			.flags = 0,
		},
		/* PCIDevice: 19:03.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x80,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0x88,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ACS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x138,
			.len = 0x8,
			.flags = 0,
		},
		/* PCIDevice: 1a:00.0 */
		/* PCIDevice: 1a:00.1 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x40,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0x18,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0x70,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0xa0,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_VPD,
			.start = 0xe0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ARI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x150,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SRIOV | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x160,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_TPH | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1a0,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ACS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1b0,
			.len = 0x8,
			.flags = 0,
		},
		/* PCIDevice: 3a:08.0 */
		/* PCIDevice: 3a:09.0 */
		/* PCIDevice: 3a:0a.0 */
		/* PCIDevice: 3a:0a.1 */
		/* PCIDevice: 3a:0a.2 */
		/* PCIDevice: 3a:0a.3 */
		/* PCIDevice: 3a:0a.4 */
		/* PCIDevice: 3a:0a.5 */
		/* PCIDevice: 3a:0a.6 */
		/* PCIDevice: 3a:0a.7 */
		/* PCIDevice: 3a:0b.0 */
		/* PCIDevice: 3a:0b.1 */
		/* PCIDevice: 3a:0b.2 */
		/* PCIDevice: 3a:0b.3 */
		/* PCIDevice: 3a:0c.0 */
		/* PCIDevice: 3a:0c.1 */
		/* PCIDevice: 3a:0c.2 */
		/* PCIDevice: 3a:0c.3 */
		/* PCIDevice: 3a:0c.4 */
		/* PCIDevice: 3a:0c.5 */
		/* PCIDevice: 3a:0c.6 */
		/* PCIDevice: 3a:0c.7 */
		/* PCIDevice: 3a:0d.0 */
		/* PCIDevice: 3a:0d.1 */
		/* PCIDevice: 3a:0d.2 */
		/* PCIDevice: 3a:0d.3 */
		/* PCIDevice: ae:08.0 */
		/* PCIDevice: ae:09.0 */
		/* PCIDevice: ae:0a.0 */
		/* PCIDevice: ae:0a.1 */
		/* PCIDevice: ae:0a.2 */
		/* PCIDevice: ae:0a.3 */
		/* PCIDevice: ae:0a.4 */
		/* PCIDevice: ae:0a.5 */
		/* PCIDevice: ae:0a.6 */
		/* PCIDevice: ae:0a.7 */
		/* PCIDevice: ae:0b.0 */
		/* PCIDevice: ae:0b.1 */
		/* PCIDevice: ae:0b.2 */
		/* PCIDevice: ae:0b.3 */
		/* PCIDevice: ae:0c.0 */
		/* PCIDevice: ae:0c.1 */
		/* PCIDevice: ae:0c.2 */
		/* PCIDevice: ae:0c.3 */
		/* PCIDevice: ae:0c.4 */
		/* PCIDevice: ae:0c.5 */
		/* PCIDevice: ae:0c.6 */
		/* PCIDevice: ae:0c.7 */
		/* PCIDevice: ae:0d.0 */
		/* PCIDevice: ae:0d.1 */
		/* PCIDevice: ae:0d.2 */
		/* PCIDevice: ae:0d.3 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x14,
			.flags = 0,
		},
		{
			.id = 0x0 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 5d:0e.1 */
		/* PCIDevice: 5d:0f.1 */
		/* PCIDevice: d7:0e.1 */
		/* PCIDevice: d7:0f.1 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0xf4,
			.flags = 0,
		},
		/* PCIDevice: 5e:00.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x50,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x68,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0xa8,
			.len = 0x18,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0xc0,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1e0,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_PWR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1c0,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_DPA | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x190,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ARI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x148,
			.len = 0x8,
			.flags = 0,
		},
	},
};
