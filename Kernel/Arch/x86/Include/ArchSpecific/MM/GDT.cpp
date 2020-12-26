#include "GDT.h"

GDTPtr globalDescriptorTablePTR;
GDTEntry* globalDescriptorTable;

u16 globalDescriptorTableLength;

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
void RegisterGDTEntry(int index, u32 limit, u32 base, u8 access, u8 flags) {
    globalDescriptorTable[index].limit_low = limit & 0xFFFF;
    globalDescriptorTable[index].base_low = base & 0xFFFF;
    globalDescriptorTable[index].base_middle = (base >> 16) & 0xFF;
    globalDescriptorTable[index].access = access;
    globalDescriptorTable[index].granularity = flags;
    globalDescriptorTable[index].base_high = (base >> 24) & 0xFF;
}

/*
* LoadGDT:
*   Loads the pointer to the new global descriptor table into the processor
* Arguments:
* Return:
*/
void LoadGDT()
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

    RegisterGDTEntry(0, 0, 0, 0, GDT_STANDARD_FLAGS);
    RegisterGDTEntry(1, 0xFFFFFFFF, 0, GDT_RING0_CODE, GDT_STANDARD_FLAGS);
    RegisterGDTEntry(2, 0xFFFFFFFF, 0, GDT_RING0_DATA, GDT_STANDARD_FLAGS);
    RegisterGDTEntry(3, 0xFFFFFFFF, 0, GDT_RING3_CODE, GDT_STANDARD_FLAGS);
    RegisterGDTEntry(4, 0xFFFFFFFF, 0, GDT_RING3_DATA, GDT_STANDARD_FLAGS);
    //RegisterGDTEntry(5, 0, 0, 0, GDT_STANDARD_FLAGS);

    LoadGDT();
}