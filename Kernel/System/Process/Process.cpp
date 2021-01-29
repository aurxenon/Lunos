#include "Process.h"

Process::Process() {
    u32 kernelStackBase = 0;
    m_pageDirectory = &(getMM().createProcessPageDirectory(true, kernelStackBase));

    m_processTSS.ss0 = TSS_SS0;
    m_processTSS.io_map_addr = (u16)TSS_IOPB;
}

Process::Process(u32 eip) {
    createMemorySpace();

    m_stackPointer -= sizeof(TrapFrame); //allocates space for a trap frame to return to
    TrapFrame* trapFrame = (TrapFrame*)m_stackPointer; //fills out a trap frame
    trapFrame->eip = eip;
    trapFrame->esp = (u32)m_stackPointer + sizeof(TrapFrame);
    trapFrame->cs = GDT_RING0_CODE_SELECTOR;
    trapFrame->ds = GDT_RING0_DATA_SELECTOR;
    trapFrame->gs = GDT_RING0_DATA_SELECTOR;
    trapFrame->fs = GDT_RING0_DATA_SELECTOR;
    trapFrame->es = GDT_RING0_DATA_SELECTOR;
    
    /*m_processTSS.ss0 = TSS_SS0; //fills out a tss
    m_processTSS.esp0 = m_stackPointer;
    m_processTSS.io_map_addr = (u16)TSS_IOPB;*/
}

void Process::createMemorySpace() {
    u32 kernelStackBase = 0;
    m_pageDirectory = &(getMM().createProcessPageDirectory(true, kernelStackBase));
    m_kernelStackBase = (void*)kernelStackBase;
    m_stackPointer = (u32)(m_kernelStackBase + (PAGE_SIZE - 1));
}

size_t Process::getAllocatedCpuTicks() {
    return m_allocatedCpuTicks;
}

void Process::setAllocatedCpuTicks(size_t ticks) {
    m_allocatedCpuTicks = ticks;
}

u32 Process::getStackPointer() {
    klog() << "Stack Pointer: " << m_stackPointer;
    return m_stackPointer;
}

void Process::setStackPointer(u32 stackPointer) {
    m_stackPointer = stackPointer;
    m_processTSS.esp0 = stackPointer;
}

void Process::loadVMSpace() {
    m_pageDirectory->load();
}

void Process::updateTSS() {
    m_processTSS.esp0 = m_stackPointer;
    RegisterGDTEntry(5, sizeof(m_processTSS) - 1, (u32)&m_processTSS, TSS_GDT_ACCESS, (sizeof(m_processTSS) - 1) >> 16 | 0b01000000);
}

TSS* Process::getTSS() {
    return &m_processTSS;
}

void Process::saveTSS(TSS tss) {
    m_processTSS = tss;
}