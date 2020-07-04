#include "Scheduler.h"

Scheduler::Scheduler() {
    m_processes = DoublyLinkedList<Process>();
    m_firstTime = true;
}

u32 Scheduler::Schedule(u32 esp) {
    if (m_firstTime) {
        m_current = new Process();
        m_firstTime = false;
    }

    m_current->setStackPointer(esp);

    if (m_processes.size() == 0) {
        klog() << " Returning to " << m_current->getStackPointer();
        return m_current->getStackPointer();
    }

    m_processes.push_back(m_current);

    m_current = m_processes.front();
    m_processes.remove(m_current);
    
    klog() << " Swapping to " << m_current->getStackPointer();

    u32 returnedStackPointer = m_current->getStackPointer();

    return returnedStackPointer;
}

void Scheduler::addProcess(void processEntryFunction(void)) {
    Process* newProcess = new Process((u32)processEntryFunction);

    m_processes.push_back(newProcess);
}