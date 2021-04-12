
#ifndef _JAILHOUSE_PGTABLE_DUMP_H
#define _JAILHOUSE_PGTABLE_DUMP_H

#include <paging.h>
#include <types.h>

typedef unsigned long addr_t;

#define INVALID_PROT ((pg_prot_t)0)
#define OUT_OF_RANGE -1

typedef struct pg_level_t {
    int pgl;
}pg_level_t;

typedef struct pg_prot_t {
    u64 p;
}pg_prot_t;

struct prot_bits {
	pg_prot_t mask;
	pg_prot_t val;
	const char *set;
	const char *clear;
};

struct range {
    addr_t start;
    addr_t end;
};

struct pg_dump_state {
    addr_t start_va;
    addr_t end_va;
    pg_prot_t p;
    struct pg_level *pgl;
};

struct pg_state {
    struct range rg;
    struct pg_dump_state pgst;
    struct paging *root_paging;
    page_table_t root_table;

    // int (*page_prot_dump)(pg_prot_t prots, pg_level_t pgl);
    // int (*page_level_dump)(pg_level_t pgl);

    int (*note_page)(struct pg_dump_state *pgst);

    pt_entry_t (*get_next_pt)(pt_entry_t pte);
    pt_entry_t (*get_next_entry)(pt_entry_t pte);
    pt_entry_t (*get_end_entry)(pt_entry_t pte);
    
    pg_prot_t (*get_mask)(pt_entry_t pte, pg_level_t pgl);
    pg_prot_t (*get_prots)(pt_entry_t pte, pg_prot_t mask, pg_level_t pgl);

    bool (*pte_present)(pt_entry_t pte, pg_level_t pgl);
    bool (*pte_pgtable)(pt_entry_t pte, pg_level_t pgl);

    pg_level_t (*get_next_pgl)(pg_level_t pgl);
};


int pgtable_dump(struct pg_state *st);
int walk_page(struct pg_state *st, pg_level_t pgl, pt_entry_t start, pt_entry_t end, pg_prot_t mask);

#endif /* _JAILHOUSE_PGTABLE_DUMP_H */