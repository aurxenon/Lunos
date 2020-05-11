#include "MemoryManager.h"

u32 page_directory[PAGE_DIR_ENTRIES] __attribute__((aligned(4096)));
u32 page_table_1[PAGE_TBL_ENTRIES] __attribute__((aligned(4096)));

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

void initializePaging() {

    //
    //creates an empty page directory
    //
    for (int i = 0; i < PAGE_DIR_ENTRIES; i++) {
        page_directory[i] = UNINITIALIZED_DIR_ENTRY;
    }

    //
    //creates a page table that maps the first 4MB of RAM
    //
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        page_table_1[i] = (i * 4096) | UNINITIALIZED_TBL_ENTRY;
    }

    //
    //places the empty page table into the page directory
    //
    page_directory[0] = ((u32)page_table_1) | UNINITIALIZED_TBL_ENTRY;

    //
    //writes the address of the page directory to the CR3 register
    //
    write_cr3((u32)page_directory);

    //
    //reads the cr0 register, enables paging bit, and then rewrites the cr0 register
    //
    u32 cr0 = read_cr0();
    cr0 = cr0 | PAGING_ENABLE;
    write_cr0(cr0);
}

/*
    This segmentation code is very heavily based on James Molloy's GDT tutorial
*/
void InitializeSegmentation() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (u32)&gdt_entries;

    GDTSetCallGate(0, 0, 0, 0, 0);                // Null segment
    GDTSetCallGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    GDTSetCallGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    GDTSetCallGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    GDTSetCallGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    LoadGDT((u32)&gdt_ptr);
}

void GDTSetCallGate(i32 num, u32 base, u32 limit, u8 access, u8 granularity)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= granularity & 0xF0;
   gdt_entries[num].access      = access;
}

void LoadGDT(u32 gdt_pointer) {
    __asm __volatile__("lgdt %0"::"m"(gdt_pointer):"memory");
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