
#ifndef _ASM_JAILHOUSE_PGTABLE_DUMP_H
#define _ASM_JAILHOUSE_PGTABLE_DUMP_H

#include <asm/paging.h>
#include <asm/vmx.h>

typedef unsigned long addr_t;

#define PAGE_LEVEL_EPT_PTE 0 
#define PAGE_LEVEL_EPT_PDE 1
#define PAGE_LEVEL_EPT_PDPTE 2
#define PAGE_LEVEL_EPT_PML4E 3
#define PAGE_LEVEL_EPT_PML5E 4

#define PTE_PAGE_SIZE (0x1UL << 12)
#define PDE_PAGE_SIZE (PTE_PAGE_SIZE << 9)
#define PDPTE_PAGE_SIZE (PTE_PAGE_SIZE << 18)
#define PML4E_PAGE_SIZE (PTE_PAGE_SIZE << 27)
#define PML5E_PAGE_SIZE (PTE_PAGE_SIZE << 36)

#define EPT_PAGE_PROT_PS (0x1UL << 7)
#define EPT_PAGE_PROT_MASK (EPT_FLAG_READ | EPT_FLAG_WRITE | EPT_FLAG_EXECUTE)
#define EPT_PAGE_PRESENT (EPT_FLAG_READ | EPT_FLAG_WRITE | EPT_FLAG_EXECUTE) 

int x86_ept_dump(page_table_t root, addr_t start, addr_t end);
#endif