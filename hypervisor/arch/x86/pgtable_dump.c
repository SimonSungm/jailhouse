#include <asm/pgtable_dump.h>
#include <asm/paging.h>
#include <asm/vmx.h>


#ifdef CONFIG_PT_DUMP
static const struct pg_state vmx_ept_st {
    .root_paging = x86_64_paging,
    .note_page = vmx_ept_note_page,
    .get_next_pt = vmx_ept_get_next_pt,
    .get_next_entry = vmx_ept_get_next_entry,
    .get_end_entry = vmx_ept_get_end_entry,
    .get_mask = vmx_ept_get_mask,
    .get_prots = vmx_ept_get_prots,
    .pte_present = vmx_ept_pte_present,
    .pte_pgtable = vmx_ept_pte_pgtable,
    .get_next_pgl = vmx_ept_get_next_pgl
};

int vmx_ept_note_page(struct pg_state *st, pt_entry_t e, pg_prot_t mask, pg_level_t pgl, bool flag)
{
    return 0;
}

pt_entry_t vmx_ept_get_next_pt(pt_entry_t pte)
{
    return paging_phys2hvirt(*pte & BIT_MASK(51, 12));
}

pt_entry_t vmx_ept_get_next_entry(pt_entry_t pte)
{
    pt_entry_t next = pte+1;
    if((next & PAGE_MASK) == next)
        return NULL;
    else
        return next;
}

pt_entry_t vmx_ept_get_end_entry(pt_entry_t pte)
{
    void *base = (void *)(pte & PAGE_MASK);
    void *end = (base + PAGE_SIZE) - sizeof(*pt_entry_t);
    return (pt_entry_t)end;
}

pg_prot_t vmx_ept_get_mask(pt_entry_t pte, pg_level_t pgl)
{
    pg_prot_t mask = {.p = BIT_MASK(63,0)};
    return mask;
}

pg_prot_t vmx_ept_get_prots(pt_entry_t pte, pg_prot_t mask, pg_level_t pgl)
{
    pg_prot_t prot = {.p = 0};
    return prot;
}

bool vmx_ept_pte_present(pt_entry_t pte, pg_level_t pgl)
{
    if((*pte) & PAGE_PROT_EPT_PRESENT)
        return true;
    return false;
}

bool vmx_ept_pte_pgtable(pt_entry_t pte, pg_level_t pgl)
{
    if(pgl.pgl == PAGE_LEVEL_EPT_PTE || 
        (pgl.pgl != PAGE_LEVEL_EPT_PML4E &&
        ((*pte) & PAGE_PROT_EPT_PS)))
        return false;
    return true;
}

pg_level_t vmx_ept_get_next_pgl(pg_level_t pgl)
{
    pg_level_t npgl = {.pgl = pgl.pgl+1};
    return npgl;
}


int x86_ept_dump()
{
    
}

int x86_pt_dump()
{

}

int i386_pt_dump()
{

}

int pae_pt_dump()
{

}

#endif