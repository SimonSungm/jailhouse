#include <jailhouse/pgtable_dump.h>
#include <jailhouse/paging.h>

#ifdef CONFIG_PT_DUMP
int pgtable_dump(struct pg_state *st)
{
    struct pg_dump_state *pgst = &(st->pgst);
    pg_prot_t init_mask = {.p = BIT_MASK(63,0)};
    pt_entry_t start, end;
    if(pgst->end_va == pgst->start_va || pgst->end_va-1 < pgst->start_va) return 0;

    start = st->root_paging[0].get_entry(st->root_table, st->rg.start);
    end = st->root_paging[0].get_entry(st->root_table, st->rg.end);
    walk_page(st, 0, start, end, init_mask);
    st->note_page(st);
}

int walk_page(struct pg_state *st, pg_level_t pgl, pt_entry_t start, pt_entry_t end, mask)
{
    struct paging *pg_ops = &(st->root_paging[pgl.pgl]);
    pt_entry_t e = start;

    while(true) {
        if(st->pte_present(e,pgl)){
            if(st->pte_pgtable(e, pgl)) {
                walk_page(st, st->get_next_pgl(pgl), st->get_next_pt(e), st->get_end_entry(next_pt), mask & st->get_mask(e, pgl));
            } else {
                st->note_page(st, e, mask, pgl, true);
            }
        } else {
            st->note_page(st, e, mask, pgl, false);
        }
        if(e == end) break;
        else e = st->get_next_entry(e);
    }
    return 0;
}
#else
int pgtable_dump(struct pg_state *st){}
int walk_page(struct pg_state *st, pg_level_t pgl, pt_entry_t start, pt_entry_t end, pg_prot_t mask){}
#endif