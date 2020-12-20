#include "PageDirectory.h"

/*
*
* PageDirectory
*
*/

PageDirectory::PageDirectory() {}

PageDirectoryEntry& PageDirectory::operator[](size_t pageDirectoryEntryIndex) {
    return m_pageDirectory[pageDirectoryEntryIndex];
}

void PageDirectory::initialize() {
    for (int i = 0; i < PAGE_DIR_ENTRIES; i++) {
        m_pageDirectory[i].clear();
    }
}

void PageDirectory::load() {
    write_cr3((u32)m_pageDirectory);
}

/*
*
* PageDirectoryEntry
*
*/

PageDirectoryEntry::PageDirectoryEntry() {
    clear();
}

void PageDirectoryEntry::clear() {
    m_pageDirectoryEntry = PD_UNINITIALIZED_ENTRY;
}

void PageDirectoryEntry::operator=(PageDirectoryEntry otherPageDirectoryEntry) {
    m_pageDirectoryEntry = otherPageDirectoryEntry.m_pageDirectoryEntry;
}

u32 PageDirectoryEntry::getPageTableAddress() {
    return m_pageDirectoryEntry & PD_ADDRESS;
}

void PageDirectoryEntry::setPageTableAddress(u32 physicalAddress) {
    m_pageDirectoryEntry &= ~PD_ADDRESS;
    m_pageDirectoryEntry |= physicalAddress;
}

PageTable& PageDirectoryEntry::getPageTable() {
    PageTable* pageTable = (PageTable*)getPageTableAddress();
    return *pageTable;
}

void PageDirectoryEntry::setPageTable(PageTable& pageTable) {
    setPageTableAddress((u32)(pageTable.m_pageTable));
}

bool PageDirectoryEntry::isPresent() {
    return m_pageDirectoryEntry & PD_PRESENT;
}

void PageDirectoryEntry::setPresent(bool isPresent) {
    if (isPresent) {
        m_pageDirectoryEntry |= PD_PRESENT;
    } else {
        m_pageDirectoryEntry &= ~PD_PRESENT;
    }
}

bool PageDirectoryEntry::isWriteable() {
    return m_pageDirectoryEntry & PD_WRITEABLE;
}

void PageDirectoryEntry::setWriteable(bool isWriteable) {
    if (isWriteable) {
        m_pageDirectoryEntry |= PD_WRITEABLE;
    } else {
        m_pageDirectoryEntry &= ~PD_WRITEABLE;
    }
}