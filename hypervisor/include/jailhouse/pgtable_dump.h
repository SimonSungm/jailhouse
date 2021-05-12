
#ifndef _JAILHOUSE_PGTABLE_DUMP_H
#define _JAILHOUSE_PGTABLE_DUMP_H

#include <jailhouse/paging.h>
#include <jailhouse/types.h>
#include <asm/pgtable_dump.h>

#define INVALID_PROT ((pg_prot_t)0)
#define OUT_OF_RANGE -1

typedef int pg_level_t;

typedef u64 pg_prot_t;

struct prot_bits {
	pg_prot_t mask;
	pg_prot_t val;
	const char *set;
	const char *clear;
};

struct pg_dump_state {
    addr_t start_va;
    addr_t end_va;
    pg_prot_t p;
    pg_level_t pgl;
};

struct pg_state {
    struct pg_dump_state pgst;

    // int (*page_prot_dump)(pg_prot_t prots, pg_level_t pgl);
    // int (*page_level_dump)(pg_level_t pgl);

    int (*note_page)(struct pg_state *st, pt_entry_t e, pg_prot_t mask, pg_level_t pgl, bool flag);

    pt_entry_t (*get_next_pt)(pt_entry_t pte);
    pt_entry_t (*get_next_entry)(pt_entry_t pte);
    pt_entry_t (*get_end_entry)(pt_entry_t pte);
    
    pg_prot_t (*get_mask)(pt_entry_t pte, pg_level_t pgl);
    pg_prot_t (*get_prots)(pt_entry_t pte, pg_level_t pgl);

    bool (*pte_present)(pt_entry_t pte, pg_level_t pgl);
    bool (*pte_pgtable)(pt_entry_t pte, pg_level_t pgl);

    pg_level_t (*get_next_pgl)(pg_level_t pgl);
    unsigned long (*get_size)(pg_level_t pgl);
};


void dump_page_table(struct pg_state *pg_st, pt_entry_t start, pt_entry_t end, pg_level_t pgl, pg_prot_t mask);

#endif /* _JAILHOUSE_PGTABLE_DUMP_H */