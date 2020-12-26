#include "MemoryManager.h"

///////////////

GDTPtr globalDescriptorTablePTR;
GDTEntry* globalDescriptorTable;

u16 globalDescriptorTableLength;

u32 contiguousMemory;

u8 memoryBitmapSpace[UINT32_MAX / PAGE_SIZE / 8];

void InitializeMemoryManager(void* kernelPageArea, multiboot_info_t* mbd) {
    if (mbd->flags & MULTIBOOT_INFO_MEMORY) {
        contiguousMemory = mbd->mem_upper + mbd->mem_lower;
        contiguousMemory *= 1024;
    }
    LibStandard::Bitmap freeMemoryBitmap(memoryBitmapSpace, UINT32_MAX / PAGE_SIZE / 8);
    
    //disable allowing allocation of any ram greater than the amount of ram present in the system
    u32 extraBytes = (u32)contiguousMemory % PAGE_SIZE;
    for (u32 i = UINT32_MAX; i > contiguousMemory - extraBytes; i -= PAGE_SIZE) { 
        freeMemoryBitmap.enableBit(i / PAGE_SIZE);
    }

    //disable allowing allocation of any ram below 1mb
    for (u32 i = 0; i < 0xFFFFF; i += PAGE_SIZE) { 
        freeMemoryBitmap.enableBit(i / PAGE_SIZE);
    }

    if (mbd->flags & MULTIBOOT_INFO_MEM_MAP) {
        multiboot_memory_map_t* memMapNode = (multiboot_memory_map_t*)mbd->mmap_addr;

        klog() << "\n" << contiguousMemory << " bytes of memory present";
        klog() << "\nSystem memory map:";

        while (memMapNode < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length)) {
            klog() << "\nstart address:" << memMapNode->addr_low << " length:" << memMapNode->len_low << " type-" << memMapNode->type;
            u32 memMapNodeStart = memMapNode->addr_low;
            u32 startExtraBytes = (u32)memMapNodeStart % PAGE_SIZE;
            memMapNodeStart -= startExtraBytes;

            if (memMapNode->type != MULTIBOOT_MEMORY_AVAILABLE) {
                u32 memMapNodeEnd = memMapNode->len_low + memMapNodeStart;
                u32 endExtraBytes = (u32)memMapNodeStart % PAGE_SIZE;
                memMapNodeEnd -= endExtraBytes;
                memMapNodeEnd += PAGE_SIZE;

                for (u32 i = memMapNodeStart; i < memMapNodeEnd; i += PAGE_SIZE) {
                    freeMemoryBitmap.enableBit(i / PAGE_SIZE);
                }
                memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
                continue;
            }

            if (memMapNode->type == MULTIBOOT_MEMORY_AVAILABLE && memMapNode->len_low < PAGE_SIZE) {
                freeMemoryBitmap.enableBit(memMapNodeStart / PAGE_SIZE);
                memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
                continue;
            }
            
            u32 lenExtraBytes = memMapNode->len_low % PAGE_SIZE;
            if (memMapNode->type == MULTIBOOT_MEMORY_AVAILABLE && lenExtraBytes != 0) {
                memMapNodeStart += memMapNode->len_low;
                memMapNodeStart -= lenExtraBytes;

                freeMemoryBitmap.enableBit(memMapNodeStart / PAGE_SIZE);
                memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
                continue;
            }
            memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
        }
    } else {
        klog() << "Unable to obtain memory map from bootloader, halting!";
        while (true) {
            asm("nop");
        }
    }
    klog() << "\n";
    CreateKernelPages(kernelPageArea);
}

/*
* CreateKernelPages:
*   Creates page table to identity map the first 4MB of RAM for kernel, loads this table
*   into the page directory, then enables paging and loads page directory into processor
* Arguments:
* Return:
*/
void CreateKernelPages(void* kernelPageArea) {
    PageDirectory& kernelPageDirectory = *((PageDirectory*)kernelPageArea);
    PageTable& kernelPageTable = *((PageTable*)(kernelPageArea + PAGE_SIZE));

    kernelPageDirectory.initialize();
    kernelPageTable.initialize();

    //
    //creates a page table that maps the first 4MB of RAM
    //
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        kernelPageTable[i].setPhysicalAddress(i * 4096);
    }

    kernelPageDirectory[0].setPageTable(kernelPageTable);
    kernelPageDirectory[0].setPresent(true);

    kernelPageDirectory.load();

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