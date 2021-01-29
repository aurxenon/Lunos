#pragma once

#include <ArchSpecific/Types.h>
#include <LibStandard/CString.h>
#include <LibStandard/new.h>

#include "MemoryManager.h"
#include "CPU.h"

#define PAGE_TBL_ENTRIES 1024

#define PT_UNINITIALIZED_ENTRY 0b00000000000000000000000000000011 //page table entry is r/w, and is present in memory
#define PT_ADDRESS             0b11111111111111111111000000000000
#define PT_PRESENT             0b00000000000000000000000000000001
#define PT_WRITEABLE           0b00000000000000000000000000000010
#define PT_SUPERVISOR          0b00000000000000000000000000000100

class MemoryManager;
extern MemoryManager& getMM();

class PageTableEntry {
    public:
        PageTableEntry();

        void clear();

        void operator=(PageTableEntry otherPageTableEntry);

        bool isPresent();
        void setPresent(bool isPresent);

        bool isSupervisorPage();
        void setSupervisorPage(bool isSupervisorOnly);

        u32 getPhysicalAddress();
        void setPhysicalAddress(u32 physicalAddress);
    private:
        u32 m_pageTableEntry;
};

void* ptOperatorNew();

class PageTable {
    public:
        PageTable();
        PageTable(PageTable& otherPageTable);

        PageTableEntry& operator[](size_t pageTableEntryIndex);
        void operator=(PageTable& otherPageTable);
        void* operator new(std::size_t size) {
            return ptOperatorNew();
        }

        void initialize();
    private:
        PageTableEntry m_pageTable[PAGE_TBL_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

        friend class PageDirectoryEntry;
};