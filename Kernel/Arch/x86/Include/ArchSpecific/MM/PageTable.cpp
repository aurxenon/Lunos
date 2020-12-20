#include "PageTable.h"

/*
*
* PageTable
*
*/

PageTable::PageTable() {}

PageTableEntry& PageTable::operator[](size_t pageTableEntryIndex) {
    return m_pageTable[pageTableEntryIndex];
}

void PageTable::initialize() {
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        m_pageTable[i].clear();
    }
}

/*
*
* PageTableEntry
*
*/

PageTableEntry::PageTableEntry() {
    clear();
}

void PageTableEntry::clear() {
    m_pageTableEntry = PT_UNINITIALIZED_ENTRY;
}

void PageTableEntry::operator=(PageTableEntry otherPageTableEntry) {
    m_pageTableEntry = otherPageTableEntry.m_pageTableEntry;
}

bool PageTableEntry::isPresent() {
    return m_pageTableEntry & PT_PRESENT;
}

void PageTableEntry::setPresent(bool isPresent) {
    if (isPresent) {
        m_pageTableEntry |= PT_PRESENT;
    } else {
        m_pageTableEntry &= ~PT_PRESENT;
    }
}

bool PageTableEntry::isSupervisorPage() {
    return m_pageTableEntry & PT_SUPERVISOR;
}

void PageTableEntry::setSupervisorPage(bool isSupervisorOnly) {
    if (isSupervisorOnly) {
        m_pageTableEntry |= PT_SUPERVISOR;
    } else {
        m_pageTableEntry &= ~PT_SUPERVISOR;
    }
}

u32 PageTableEntry::getPhysicalAddress() {
    return m_pageTableEntry & PT_ADDRESS;
}

void PageTableEntry::setPhysicalAddress(u32 physicalAddress) {
    m_pageTableEntry &= ~PT_ADDRESS;
    m_pageTableEntry |= physicalAddress;
}