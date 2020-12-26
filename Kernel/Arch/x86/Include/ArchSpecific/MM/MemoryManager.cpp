#include "MemoryManager.h"

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