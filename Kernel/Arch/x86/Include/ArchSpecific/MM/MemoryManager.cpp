#include "MemoryManager.h"

static MemoryManager* memManager;

/*
* getMM:
*   Get the memory manager instance
* Arguments:
* Return:
*   MemoryManager& - reference to MemoryManager currently in use
*/
MemoryManager& getMM() {
    return *memManager;
}

/*
* MemoryManager::MemoryManager:
*   Create a memory bitmap and also setup paging
* Arguments:
*   kernelPageArea - region in memory to be used for initial kernel page table and kernel page directory
*   mbd - multiboot flags, used to create memory bitmap
* Return:
*/
MemoryManager::MemoryManager(void* kernelPageArea, multiboot_info_t* mbd) : m_freeMemoryBitmap(*(new LibStandard::Bitmap(m_memoryBitmapSpace, UINT32_MAX / PAGE_SIZE / 8))) {
    m_isPaging = false;
    memManager = this;
    
    if (mbd->flags & MULTIBOOT_INFO_MEMORY) {
        m_contiguousMemory = mbd->mem_upper + mbd->mem_lower;
        m_contiguousMemory *= 1024;
    }
    
    //disable allowing allocation of any ram greater than the amount of ram present in the system
    u32 extraBytes = (u32)m_contiguousMemory % PAGE_SIZE;
    for (u32 i = UINT32_MAX; i > m_contiguousMemory - extraBytes; i -= PAGE_SIZE) { 
        m_freeMemoryBitmap.enableBit(i / PAGE_SIZE);
    }

    //disable allowing allocation of any ram below 4mb
    for (u32 i = 0; i < 0x3FFFFC; i += PAGE_SIZE) { 
        m_freeMemoryBitmap.enableBit(i / PAGE_SIZE);
    }

    if (mbd->flags & MULTIBOOT_INFO_MEM_MAP) {
        multiboot_memory_map_t* memMapNode = (multiboot_memory_map_t*)mbd->mmap_addr;

        klog() << "\n" << m_contiguousMemory << " bytes of memory present";
        klog() << "\nSystem memory map:";

        while (memMapNode < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length)) {
            klog() << "\nstart address:" << memMapNode->addr_low << " length:" << memMapNode->len_low << " type-" << memMapNode->type;
            u32 memMapNodeStart = memMapNode->addr_low;
            //4kb align starting address of memory region
            u32 startExtraBytes = (u32)memMapNodeStart % PAGE_SIZE;
            memMapNodeStart -= startExtraBytes;

            if (memMapNode->type != MULTIBOOT_MEMORY_AVAILABLE) {
                //4kb align unavailable memory region
                u32 memMapNodeEnd = memMapNode->len_low + memMapNodeStart;
                u32 endExtraBytes = (u32)memMapNodeStart % PAGE_SIZE;
                memMapNodeEnd -= endExtraBytes;
                memMapNodeEnd += PAGE_SIZE;

                for (u32 i = memMapNodeStart; i < memMapNodeEnd; i += PAGE_SIZE) {
                    m_freeMemoryBitmap.enableBit(i / PAGE_SIZE);
                }
                memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
                continue;
            }
            
            //if the memory region is available but is smaller than a page, don't use it
            if (memMapNode->type == MULTIBOOT_MEMORY_AVAILABLE && memMapNode->len_low < PAGE_SIZE) {
                m_freeMemoryBitmap.enableBit(memMapNodeStart / PAGE_SIZE);
                memMapNode = (multiboot_memory_map_t*)((u32)memMapNode + memMapNode->size + sizeof(memMapNode->size));
                continue;
            }
            
            //if the memory region is available but not 4kb aligned, align it
            u32 lenExtraBytes = memMapNode->len_low % PAGE_SIZE;
            if (memMapNode->type == MULTIBOOT_MEMORY_AVAILABLE && lenExtraBytes != 0) {
                memMapNodeStart += memMapNode->len_low;
                memMapNodeStart -= lenExtraBytes;

                m_freeMemoryBitmap.enableBit(memMapNodeStart / PAGE_SIZE);
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
    createKernelAddressSpace(kernelPageArea);
}

/*
* MemoryManager::createKernelAddressSpace:
*   Setup paging, create virtual memory space with kernel regions present
* Arguments:
*   kernelPageArea - region in memory to be used for initial kernel page table and kernel page directory
* Return:
*/
void MemoryManager::createKernelAddressSpace(void* kernelPageArea) {
    m_kernelPageDirectory = (PageDirectory*)kernelPageArea;
    m_kernelPageTable = (PageTable*)(kernelPageArea + PAGE_SIZE);
    
    (*m_kernelPageDirectory).initialize();
    (*m_kernelPageTable).initialize();

    //
    //creates a page table that maps the first 4MB of RAM
    //
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        (*m_kernelPageTable)[i].setPhysicalAddress(i * PAGE_SIZE);
    }

    for (int i = KERNEL_PAGE_TABLES_START; i < PAGE_DIR_ENTRIES; i++) {
        (*m_kernelPageDirectory)[i].setPageTable(*(new PageTable()));
        (*m_kernelPageDirectory)[i].setPresent(true);
        (*m_kernelPageDirectory)[i].getPageTable().initialize();
        for (int x = 0; x < PAGE_TBL_ENTRIES; x++) {
            u32 ptPhysAddr = ((i - KERNEL_PAGE_TABLES_START) * (PAGE_DIR_ENTRIES * PAGE_SIZE)) + (x * PAGE_SIZE);
            (*m_kernelPageDirectory)[i][x].setPhysicalAddress(ptPhysAddr);
            (*m_kernelPageDirectory)[i][x].setPresent(true);
            (*m_kernelPageDirectory)[i][x].setSupervisorPage(true);
        }
    }

    (*m_kernelPageDirectory)[0].setPageTable(*m_kernelPageTable);
    (*m_kernelPageDirectory)[0].setPresent(true);

    (*m_kernelPageDirectory).load();

    //
    //reads the cr0 register, enables paging bit, and then rewrites the cr0 register
    //
    u32 cr0 = read_cr0();
    cr0 = cr0 | PAGING_ENABLE;
    write_cr0(cr0);

    m_isPaging = true;
}

/*
* MemoryManager::MemoryManager:
*   Create a process' virtual memory space
* Arguments:
*   isKernel - is the process a kernel process or userspace process
*   kernelStack - this is the kernel's stack region granted to the process
* Return:
*   PageDirectory& - process' virtual memory space
*/
PageDirectory& MemoryManager::createProcessPageDirectory(bool isKernel, u32& kernelStack) {
    kernelStack = (u32)getFreeKernelPage();
    return *(new PageDirectory(*m_kernelPageDirectory));
}

/*
* MemoryManager::physicalAddressFromVirtualAddress:
*   Convert a virtual address to a physical address
* Arguments:
*   virtualAddress - the physical address to be converted
* Return:
*   void* - physical address of virtual address
*/
void* MemoryManager::physicalAddressFromVirtualAddress(void* virtualAddress) {
    return virtualAddress - KERNEL_OFFSET;
}

/*
* MemoryManager::virtualAddressFromPhysicalAddress:
*   Convert a virtual address to a physical address
* Arguments:
*   physicalAddress - the physical address to be converted
* Return:
*   void* - virtual address of physical address
*/
void* MemoryManager::virtualAddressFromPhysicalAddress(void* physicalAddress) {
    return physicalAddress + KERNEL_OFFSET;
}

/*
* MemoryManager::getFreePhysicalPage:
*   Find an empty physical page and return it for usage
* Arguments:
* Return:
*   void* - address of physical page
*/
void* MemoryManager::getFreePhysicalPage() {
    //find first empty page and return it
    for (u32 i = 0; i < MEMORY_BITMAP_SIZE; i++) {
        if (!m_freeMemoryBitmap.getBit(i)) {
            m_freeMemoryBitmap.enableBit(i);

            return (void*)(i * PAGE_SIZE);
        }
    }

    return nullptr;
}

/*
* MemoryManager::getFreeKernelPage:
*   Wrapper to convert physical address of free physical page to virtual address
* Arguments:
* Return:
*   void* - physical address of kernel page
*/
void* MemoryManager::getFreeKernelPage() {
    return getFreePhysicalPage() + KERNEL_OFFSET;
}

/*
* MemoryManager::isPagingEnabled:
*   Is paging enabled on the system?
* Arguments:
* Return:
*   bool - true if paging is enabled, else false
*/
bool MemoryManager::isPagingEnabled() {
    return m_isPaging;
}