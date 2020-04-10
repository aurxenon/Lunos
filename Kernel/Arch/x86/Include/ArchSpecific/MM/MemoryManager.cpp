#include "MemoryManager.h"

u32 page_directory[PAGE_DIR_ENTRIES] __attribute__((aligned(4096)));
u32 page_table_1[PAGE_TBL_ENTRIES] __attribute__((aligned(4096)));

void initializePaging() {
    for (int i = 0; i < PAGE_DIR_ENTRIES; i++) {
        page_directory[i] = UNINITIALIZED_DIR_ENTRY;
    }
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        page_table_1[i] = (i * 4096) | UNINITIALIZED_TBL_ENTRY;
    }
    page_directory[0] = ((u32)page_table_1) | UNINITIALIZED_TBL_ENTRY;

    write_cr3((u32)page_directory);
    u32 cr0 = read_cr0();
    cr0 = cr0 | PAGING_ENABLE;
    write_cr0(cr0);
}

void write_cr3(u32 value) {
    __asm __volatile__(
        "movl %0, %%cr3" ::"r"(value):"memory" 
    );
}

void write_cr0(u32 value) {
    __asm __volatile__(
        "movl %0, %%cr0" ::"r"(value):"memory" 
    );
}

u32 read_cr0() {
    u32 value;
    __asm __volatile__(
        "movl %%cr0, %0":"=r"(value)::"memory" 
    );
    return value;
}