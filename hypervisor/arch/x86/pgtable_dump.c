#include <jailhouse/pgtable_dump.h>
#include <jailhouse/printk.h>
#include <asm/pgtable_dump.h>
#include <asm/paging.h>
#include <asm/vmx.h>

static int vmx_ept_note_page(struct pg_state *st, pt_entry_t e, pg_prot_t mask, pg_level_t pgl, bool flag)
{
    char dim[] = "BKMGTP-------";
    char *mapping[] = {"4KiB", "2MiB", "1GiB", "MEANLESS", "MEANLESS"};
    int index = 0;

    struct pg_dump_state *state = &(st->pgst);
    unsigned long size;
    if(!flag || state->p != (st->get_prots(e, pgl) & mask) || state->pgl != pgl) {
        size = state->end_va - state->start_va;
        if(size) {
            while(size / 1024 != 0){
                size /= 1024;
                index ++;
            }
            //printk("flag:%s, state->p:0x%016llx, 0x%016llx, pgl:%d, %d\n", flag ? "true" : "false", state->p, st->get_prots(e, pgl) & mask, state->pgl, pgl);
            printk("0x%016lx ----- 0x%016lx\t\tsize: %ld%ciB\t\tmapping:%s\t\t%c%c%c\n", state->start_va, state->end_va-1, size, dim[index], 
                mapping[state->pgl] ,(state->p & EPT_FLAG_READ)?'R':' ', (state->p & EPT_FLAG_WRITE)?'W':' ', (state->p & EPT_FLAG_EXECUTE)?'X':' ');
        }
        state->start_va = state->end_va;
        if(flag) {
            state->pgl = pgl;
            state->p = st->get_prots(e, pgl) & mask;
        }
    }
    state->end_va += st->get_size(pgl);
    if(!flag)
        state->start_va = state->end_va;
    return 0;
}

static pt_entry_t vmx_ept_get_next_pt(pt_entry_t pte)
{
    return paging_phys2hvirt(*pte & BIT_MASK(51, 12));
}

static pt_entry_t vmx_ept_get_next_entry(pt_entry_t pte)
{
    pt_entry_t next = pte+1;
    if(((unsigned long)next & PAGE_OFFS_MASK) == 0)
        return NULL;
    else
        return next;
}

static pt_entry_t vmx_ept_get_end_entry(pt_entry_t pte)
{
    void *base = (void *)((unsigned long)pte & PAGE_MASK);
    pt_entry_t end = (pt_entry_t)(((unsigned long)base + PAGE_SIZE))-1;
    return (pt_entry_t)end;
}

static pg_prot_t vmx_ept_get_prots(pt_entry_t pte, pg_level_t pgl)
{
    pg_prot_t prot = (*pte) & EPT_PAGE_PROT_MASK;
    return prot;
}

static pg_prot_t vmx_ept_get_mask(pt_entry_t pte, pg_level_t pgl)
{
    pg_prot_t mask = vmx_ept_get_prots(pte, pgl);
    return mask;
}

static bool vmx_ept_pte_present(pt_entry_t pte, pg_level_t pgl)
{
    if((*pte) & EPT_PAGE_PRESENT)
        return true;
    return false;
}

static bool vmx_ept_pte_pgtable(pt_entry_t pte, pg_level_t pgl)
{
    if(pgl == PAGE_LEVEL_EPT_PTE || 
        (pgl != PAGE_LEVEL_EPT_PML4E &&
        ((*pte) & EPT_PAGE_PROT_PS)))
        return false;
    return true;
}

static pg_level_t vmx_ept_get_next_pgl(pg_level_t pgl)
{
    pg_level_t npgl = pgl-1;
    return npgl;
}

static unsigned long vmx_ept_get_size(pg_level_t pgl)
{
    switch(pgl) {
        case PAGE_LEVEL_EPT_PTE: 
            return PTE_PAGE_SIZE;
        case PAGE_LEVEL_EPT_PDE: 
            return PDE_PAGE_SIZE;
        case PAGE_LEVEL_EPT_PDPTE:
            return PDPTE_PAGE_SIZE;
        case PAGE_LEVEL_EPT_PML4E:
            return PML4E_PAGE_SIZE;
        case PAGE_LEVEL_EPT_PML5E:
            return PML5E_PAGE_SIZE;
        default:
            printk("the pgl is too large\n");
            return 0;
    }
}

static struct pg_state vmx_ept_st = {
    .note_page = vmx_ept_note_page,
    .get_next_pt = vmx_ept_get_next_pt,
    .get_next_entry = vmx_ept_get_next_entry,
    .get_end_entry = vmx_ept_get_end_entry,
    .get_mask = vmx_ept_get_mask,
    .get_prots = vmx_ept_get_prots,
    .pte_present = vmx_ept_pte_present,
    .pte_pgtable = vmx_ept_pte_pgtable,
    .get_next_pgl = vmx_ept_get_next_pgl,
    .get_size = vmx_ept_get_size
};


int x86_ept_dump(page_table_t root, addr_t start, addr_t end)
{
    vmx_ept_st.pgst.start_va = start;
    vmx_ept_st.pgst.end_va = start;
    vmx_ept_st.pgst.pgl = 0;
    vmx_ept_st.pgst.p = 0;
    dump_page_table(&vmx_ept_st, x86_64_paging[0].get_entry(root, start), 
        x86_64_paging[0].get_entry(root, end-1), PAGE_LEVEL_EPT_PML4E, BIT_MASK(63,0));
    //printk("Finish Dump page table\n");
    vmx_ept_st.note_page(&vmx_ept_st, NULL, 0, 0, false);
    //printk("Finish Dump page table again\n");
    return 0;
}

// int x86_pt_dump()
// {

// }

// int i386_pt_dump()
// {

// }

// int pae_pt_dump()
// {

// }
