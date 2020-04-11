#include "MemoryManager.h"

u32 page_directory[PAGE_DIR_ENTRIES] __attribute__((aligned(4096)));
u32 page_table_1[PAGE_TBL_ENTRIES] __attribute__((aligned(4096)));

void initializePaging() {
    
    //creates an empty page directory
    for (int i = 0; i < PAGE_DIR_ENTRIES; i++) {
        page_directory[i] = UNINITIALIZED_DIR_ENTRY;
    }

    //creates a page table that maps the first 4MB of RAM
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        page_table_1[i] = (i * 4096) | UNINITIALIZED_TBL_ENTRY;
    }

    //places the empty page table into the page directory
    page_directory[0] = ((u32)page_table_1) | UNINITIALIZED_TBL_ENTRY;

    //writes the address of the page directroy to the CR3 register
    write_cr3((u32)page_directory);

    //reads the cr0 register, enables paging, and then rewrites the cr0 register
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