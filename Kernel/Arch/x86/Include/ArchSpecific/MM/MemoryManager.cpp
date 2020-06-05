#include "MemoryManager.h"

u32 page_directory[PAGE_DIR_ENTRIES] __attribute__((aligned(4096)));
u32 page_table_1[PAGE_TBL_ENTRIES] __attribute__((aligned(4096)));

///////////////

GDTPtr globalDescriptorTablePTR;
GDTEntry* globalDescriptorTable;

u16 globalDescriptorTableLength;

/*
* RegisterGDTEntry:
*   Creates page table to identity map the first 4MB of RAM, loads this table
*   into the page directory, then enables paging and loads page directory into processor
* Arguments:
* Return:
*/
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
* RegisterGDTEntry:
*   Creates a new GDT entry using given arguments and stores it in GDT array
* Arguments:
*   index - integer corresponding to where in the GDT the entry should be placed
*   limit - memory address of end of GDT region
*   base - memory address of start of GDT region
*   flags - bit array that controls read/write/execution of gdt region among other things
* Return:
*/
static void RegisterGDTEntry(int index, u32 limit, u32 base, u8 flags) {
    globalDescriptorTable[index].limit_low = limit & 0xFFFF;
    globalDescriptorTable[index].base_low = base & 0xFFFF;
    globalDescriptorTable[index].base_middle = (base >> 16) & 0xFF;
    globalDescriptorTable[index].access = flags;
    globalDescriptorTable[index].granularity = GDT_GRANULARITY;
    globalDescriptorTable[index].base_high = (base >> 24) & 0xFF;
}

/*
* LoadGDT:
*   Loads the pointer to the new global descriptor table into the processor
* Arguments:
* Return:
*/
static inline void LoadGDT()
{
    asm("lgdt %0"::"m"(globalDescriptorTablePTR));
}

/*
* InitializeSegmentation:
*   Creates 5 overlapping GDT entries that opens the whole x86 protected memory space
*   to the user and kernel for reading/writing/executing
* Arguments:
* Return:
*/
void InitializeSegmentation() {
    globalDescriptorTable = (GDTEntry*)kmalloce(sizeof(GDTEntry) * GDT_MAX_ENTRIES);

    globalDescriptorTableLength = GDT_NUM_ENTRIES;

    globalDescriptorTablePTR.address = globalDescriptorTable;
    globalDescriptorTablePTR.size = (globalDescriptorTableLength * sizeof(GDTEntry)) - 1;

    RegisterGDTEntry(0, 0, 0, 0);
    RegisterGDTEntry(1, 0xFFFFFFFF, 0, GDT_RING0_CODE);
    RegisterGDTEntry(2, 0xFFFFFFFF, 0, GDT_RING0_DATA);
    RegisterGDTEntry(3, 0xFFFFFFFF, 0, GDT_RING3_CODE);
    RegisterGDTEntry(4, 0xFFFFFFFF, 0, GDT_RING3_DATA);

    LoadGDT();
}