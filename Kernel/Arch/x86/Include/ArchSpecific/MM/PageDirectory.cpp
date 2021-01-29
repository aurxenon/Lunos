#include "PageDirectory.h"

/*
*
* PageDirectory
*
*/

/*
* PageDirectory::PageDirectory:
*   Creates a blank page directory
* Arguments:
* Return:
*/
PageDirectory::PageDirectory() {
    initialize();
}

/*
* PageDirectory::PageDirectory:
*   otherPageDirectory - initializes page directory as copy of other page directory
* Arguments:
* Return:
*/
PageDirectory::PageDirectory(PageDirectory& otherPageDirectory) {
    memcpy(m_pageDirectory, otherPageDirectory.m_pageDirectory, PAGE_DIR_ENTRIES * sizeof(PageDirectoryEntry));
}

/*
* PageDirectory::operator[]:
*   Returns an entry within the page directory
* Arguments:
*   pageDirectoryEntryIndex - entry of page directory to be read
* Return:
*   page directory entry at index
*/
PageDirectoryEntry& PageDirectory::operator[](size_t pageDirectoryEntryIndex) {
    return m_pageDirectory[pageDirectoryEntryIndex];
}

/*
* PageDirectory::operator=:
*   Initializes a copy of another page directory
* Arguments:
*   otherPageDirectory - Another page directory to be copied
* Return:
*/
void PageDirectory::operator=(PageDirectory& otherPageDirectory) {
    memcpy(m_pageDirectory, otherPageDirectory.m_pageDirectory, PAGE_DIR_ENTRIES * sizeof(PageDirectoryEntry));
}

/*
* PageDirectory::initialize:
*   Loops through page directory entries and sets all entries to uninitialized
* Arguments:
* Return:
*/
void PageDirectory::initialize() {
    for (int i = 0; i < PAGE_DIR_ENTRIES; i++) {
        m_pageDirectory[i].clear();
    }
}

/*
* PageDirectory::load:
*   Loads page directory address into CR3 register
* Arguments:
* Return:
*/
void PageDirectory::load() {
    if (((u32)m_pageDirectory) < KERNEL_OFFSET) {
        write_cr3((u32)m_pageDirectory);   
    } else {
        write_cr3((u32)getMM().physicalAddressFromVirtualAddress(m_pageDirectory));
    }
}

/*
* pdOperatorNew:
*   Utility function for initializing a new page directory
* Arguments:
* Return:
*   void* - pointer to new page directory
*/
void* pdOperatorNew() {
    PageDirectory* newPD;
    if (getMM().isPagingEnabled()) {
        newPD = (PageDirectory*)(getMM().getFreeKernelPage());
    } else {
        newPD = (PageDirectory*)(getMM().getFreePhysicalPage());
    }
    newPD->initialize();
    return newPD;
}

/*
*
* PageDirectoryEntry
*
*/

/*
* PageDirectory::initialize:
*   Loops through page directory entries and sets all entries to uninitialized
* Arguments:
* Return:
*/
PageDirectoryEntry::PageDirectoryEntry() {
    clear();
}

void PageDirectoryEntry::clear() {
    m_pageDirectoryEntry = PD_UNINITIALIZED_ENTRY;
}

/*
* PageDirectoryEntry::operator=:
*   Copies contents of other page directory entry into this page directory entry
* Arguments:
*   otherPageDirectoryEntry - other page directory entry to copy data from
* Return:
*/
void PageDirectoryEntry::operator=(PageDirectoryEntry otherPageDirectoryEntry) {
    m_pageDirectoryEntry = otherPageDirectoryEntry.m_pageDirectoryEntry;
}

/*
* PageDirectoryEntry::operator[]:
*   Returns reference to page directory entry
* Arguments:
*   pageTableIndex - index of page table entry
* Return:
*   PageTableEntry& - reference to page table entry pointed to by page directory entry
*/
PageTableEntry& PageDirectoryEntry::operator[](size_t pageTableIndex) {
    return (getPageTable())[pageTableIndex];
}

/*
* PageDirectoryEntry::getPhysicalPageTableAddress:
*   Returns physical address of page table pointed to by page directory entry
* Arguments:
* Return:
*   u32 - physical address of page table pointed to
*/
u32 PageDirectoryEntry::getPhysicalPageTableAddress() {
    return m_pageDirectoryEntry & PD_ADDRESS;
}

/*
* PageDirectoryEntry::setPhysicalPageTableAddress:
*   Forcibly sets the physical address for the page table pointed towards
* Arguments:
*   physicalAddress - physical address to point towards for page table
* Return:
*/
void PageDirectoryEntry::setPhysicalPageTableAddress(u32 physicalAddress) {
    m_pageDirectoryEntry &= ~PD_ADDRESS;
    m_pageDirectoryEntry |= physicalAddress;
}

/*
* PageDirectoryEntry::getPageTable:
*   Gets the page table pointed to by this page directory entry
* Arguments:
* Return:
*   PageTable& - the page table pointed to by this page directory entry
*/
PageTable& PageDirectoryEntry::getPageTable() {
    PageTable* pageTable;
    if (getMM().isPagingEnabled()) {
        pageTable = (PageTable*)(getMM().virtualAddressFromPhysicalAddress((void*)getPhysicalPageTableAddress()));
    } else {
        pageTable = (PageTable*)getPhysicalPageTableAddress();
    }
    return *pageTable;
}

/*
* PageDirectoryEntry::setPageTable:
*   Sets the page table pointed to by page directory entry
* Arguments:
*   pageTable - reference to page table to be pointed towards
* Return:
*/
void PageDirectoryEntry::setPageTable(PageTable& pageTable) {
    if ((u32)pageTable.m_pageTable < KERNEL_OFFSET) {
        setPhysicalPageTableAddress((u32)(pageTable.m_pageTable));
    } else {
        setPhysicalPageTableAddress((u32)getMM().physicalAddressFromVirtualAddress((void*)(pageTable.m_pageTable)));
    }
}

/*
* PageDirectoryEntry::isPresent:
*   Returns if the page directory entry is present in memory or no
* Arguments:
* Return:
*   bool - true is page directory entry is present, otherwise no
*/
bool PageDirectoryEntry::isPresent() {
    return m_pageDirectoryEntry & PD_PRESENT;
}

/*
* PageDirectoryEntry::setPresent:
*   Set page directory entry as being currently present/not present in memory
* Arguments:
*   isPresent - true if present in memory, false otherwise
* Return:
*/
void PageDirectoryEntry::setPresent(bool isPresent) {
    if (isPresent) {
        m_pageDirectoryEntry |= PD_PRESENT;
    } else {
        m_pageDirectoryEntry &= ~PD_PRESENT;
    }
}

/*
* PageDirectoryEntry::isWriteable:
*   Check if page table is writeable
* Arguments:
* Return:
*   true if writeable, false if not writeable
*/
bool PageDirectoryEntry::isWriteable() {
    return m_pageDirectoryEntry & PD_WRITEABLE;
}

/*
* PageDirectoryEntry::setWriteable:
*   Allows page table to be written/not written to
* Arguments:
*   isWriteable - true for allowing writing, false for disallowing writing
* Return:
*/
void PageDirectoryEntry::setWriteable(bool isWriteable) {
    if (isWriteable) {
        m_pageDirectoryEntry |= PD_WRITEABLE;
    } else {
        m_pageDirectoryEntry &= ~PD_WRITEABLE;
    }
}