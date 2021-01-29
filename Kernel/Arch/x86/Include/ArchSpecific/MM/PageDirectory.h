#pragma once

#include <ArchSpecific/Types.h>
#include <LibStandard/CString.h>
#include <LibStandard/new.h>

#include "MemoryManager.h"
#include "PageTable.h"
#include "CPU.h"

#define PAGE_DIR_ENTRIES 1024

#define PD_UNINITIALIZED_ENTRY 0b00000000000000000000000000000010 //the page directory entry is not present in the cpu
#define PD_ADDRESS             0b11111111111111111111000000000000
#define PD_WRITEABLE           0b00000000000000000000000000000010
#define PD_PRESENT             0b00000000000000000000000000000001

class PageTable;
class PageTableEntry;

class PageDirectoryEntry {
    public:
        PageDirectoryEntry();

        void clear();

        void operator=(PageDirectoryEntry otherPageDirectoryEntry);
        PageTableEntry& operator[](size_t pageTableIndex);

        u32 getPhysicalPageTableAddress();
        void setPhysicalPageTableAddress(u32 physicalAddress);

        PageTable& getPageTable();
        void setPageTable(PageTable& pageTable);

        bool isPresent();
        void setPresent(bool isPresent);

        bool isWriteable();
        void setWriteable(bool isWriteable);
    private:
        u32 m_pageDirectoryEntry;
};

void* pdOperatorNew();

class PageDirectory {
    public:
        PageDirectory();
        PageDirectory(PageDirectory& otherPageDirectory);
        void* operator new(std::size_t size) {
            return pdOperatorNew();
        }

        PageDirectoryEntry& operator[](size_t pageDirectoryEntryIndex);
        void operator=(PageDirectory& otherPageDirectory);

        void initialize();

        void load();
    private:
        PageDirectoryEntry m_pageDirectory[PAGE_DIR_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
};