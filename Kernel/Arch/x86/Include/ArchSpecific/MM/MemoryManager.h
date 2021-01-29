#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>
#include <ArchSpecific/multiboot.h>
#include <LibStandard/Bitmap.h>
#include <LibStandard/CString.h>

#include "PageTable.h"
#include "PageDirectory.h"
#include "CPU.h"

#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE
#define MEMORY_BITMAP_SIZE (UINT32_MAX / PAGE_SIZE)
#define KERNEL_PAGE_TABLES_START 512
#define KERNEL_OFFSET 0x80000000

static u8 memoryBitmapSpace[MEMORY_BITMAP_SIZE / BITS_PER_BYTE];

class MemoryManager;
class PageTable;
class PageDirectory;

MemoryManager& getMM();

class MemoryManager {
    public:
        MemoryManager(void* kernelPageArea, multiboot_info_t* mbd);

        void createKernelAddressSpace(void* kernelPageArea);

        PageDirectory& createProcessPageDirectory(bool isKernel, u32& kernelStack);

        void* physicalAddressFromVirtualAddress(void* virtualAddress);
        void* virtualAddressFromPhysicalAddress(void* physicalAddress);

        void* getFreePhysicalPage();
        void* getFreeKernelPage();

        bool isPagingEnabled();
    private:
        u8* m_memoryBitmapSpace = memoryBitmapSpace;
        u32 m_contiguousMemory;
        PageDirectory* m_kernelPageDirectory;
        PageTable* m_kernelPageTable;
        LibStandard::Bitmap& m_freeMemoryBitmap;

        bool m_isPaging;
};