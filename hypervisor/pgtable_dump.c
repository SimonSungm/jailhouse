#include <jailhouse/pgtable_dump.h>
#include <asm/pgtable_dump.h>

void dump_page_table(struct pg_state *pg_st, pt_entry_t start, pt_entry_t end, pg_level_t pgl, pg_prot_t mask)
{
    pt_entry_t walker;
    pt_entry_t next;

    for(walker = start; walker <= end; ++ walker){
        if(pg_st->pte_present(walker, pgl)){
            if(pg_st->pte_pgtable(walker, pgl)){
                next = pg_st->get_next_pt(walker);
                dump_page_table(pg_st, next, pg_st->get_end_entry(next), pg_st->get_next_pgl(pgl), mask & pg_st->get_mask(walker, pgl));
            } else {
                pg_st->note_page(pg_st, walker, mask, pgl, true);
            }
        } else {
            pg_st->note_page(pg_st, walker, mask, pgl, false);
        }
    }
}