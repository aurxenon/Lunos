#include "PageTable.h"

/*
*
* PageTable
*
*/

/*
* PageTable::PageTable:
*   Creates new page table
* Arguments:
* Return:
*/
PageTable::PageTable() {
    initialize();
}

/*
* PageTable::PageTable:
*   Creates new page table using data from other page table
* Arguments:
* Return:
*/
PageTable::PageTable(PageTable& otherPageTable) {
    memcpy(m_pageTable, otherPageTable.m_pageTable, PAGE_TBL_ENTRIES * sizeof(PageTableEntry));
}

/*
* PageTable::operator[]:
*   Returns page table entry from page table
* Arguments:
*   pageTableEntryIndex - index of page table entry to be returned
* Return:
*   PageTableEntry& - page table entry specified by pageTableEntryIndex
*/
PageTableEntry& PageTable::operator[](size_t pageTableEntryIndex) {
    return m_pageTable[pageTableEntryIndex];
}

/*
* PageTable::operator=:
*   Copies data from other page table into this page table
* Arguments:
* Return:
*/
void PageTable::operator=(PageTable& otherPageTable) {
    memcpy(m_pageTable, otherPageTable.m_pageTable, PAGE_TBL_ENTRIES * sizeof(PageTableEntry));
}

/*
* PageTable::initialize:
*   Recursively set all page table entries to uninitialized
* Arguments:
* Return:
*/
void PageTable::initialize() {
    for (int i = 0; i < PAGE_TBL_ENTRIES; i++) {
        m_pageTable[i].clear();
    }
}

/*
* ptOperatorNew:
*   Wrapper for operator new to create a new page table
* Arguments:
* Return:
*   void* - pointer to new page table
*/
void* ptOperatorNew() {
    PageTable* newPT;
    if (getMM().isPagingEnabled()) {
        newPT = (PageTable*)(getMM().getFreeKernelPage());
    } else {
        newPT = (PageTable*)(getMM().getFreePhysicalPage());
    }
    newPT->initialize();
    return newPT;
}

/*
*
* PageTableEntry
*
*/

/*
* PageTableEntry::PageTableEntry:
*   Initialize a blank page table entry
* Arguments:
* Return:
*/
PageTableEntry::PageTableEntry() {
    clear();
}

/*
* PageTableEntry::clear:
*   Reset page table entry to point to uninitialized
* Arguments:
* Return:
*/
void PageTableEntry::clear() {
    m_pageTableEntry = PT_UNINITIALIZED_ENTRY;
}

/*
* PageTableEntry::operator=:
*   Copy other page table entry into this page table entry
* Arguments:
*   otherPageTableEntry - other page table to copy data from
* Return:
*/
void PageTableEntry::operator=(PageTableEntry otherPageTableEntry) {
    m_pageTableEntry = otherPageTableEntry.m_pageTableEntry;
}

/*
* PageTableEntry::isPresent:
*   Get if this page is present in memory
* Arguments:
* Return:
*   bool - if true, this page is present in memory
*/
bool PageTableEntry::isPresent() {
    return m_pageTableEntry & PT_PRESENT;
}

/*
* PageTableEntry::setPresent:
*   Sets whether or not the page being referenced is present in memory or not
* Arguments:
*   isPresent - true if the page is present in memory
* Return:
*/
void PageTableEntry::setPresent(bool isPresent) {
    if (isPresent) {
        m_pageTableEntry |= PT_PRESENT;
    } else {
        m_pageTableEntry &= ~PT_PRESENT;
    }
}

/*
* PageTableEntry::isSupervisorPage:
*   Get if this page can only be accessed by the kernel
* Arguments:
* Return:
*   bool - if true, this page can only be accessed by the kernel
*/
bool PageTableEntry::isSupervisorPage() {
    return m_pageTableEntry & PT_SUPERVISOR;
}

/*
* PageTableEntry::setSupervisorPage:
*   Set if this page can only be accessed by the kernel
* Arguments:
*   isSupervisorOnly - if true, this page can only be accessed by the kernel
* Return:
*/
void PageTableEntry::setSupervisorPage(bool isSupervisorOnly) {
    if (isSupervisorOnly) {
        m_pageTableEntry |= PT_SUPERVISOR;
    } else {
        m_pageTableEntry &= ~PT_SUPERVISOR;
    }
}

/*
* PageTableEntry::getPhysicalAddress:
*   Get the physical address being referenced by the page table entry
* Arguments:
* Return:
*   u32 - the physical address pointed at by this page table entry
*/
u32 PageTableEntry::getPhysicalAddress() {
    return m_pageTableEntry & PT_ADDRESS;
}

/*
* PageTableEntry::setPhysicalAddress:
*   Set the physical address being referenced by the page table entry
* Arguments:
*   physicalAddress - the physical address this page table entry will refer to
* Return:
*/
void PageTableEntry::setPhysicalAddress(u32 physicalAddress) {
    m_pageTableEntry &= ~PT_ADDRESS;
    m_pageTableEntry |= physicalAddress;
}