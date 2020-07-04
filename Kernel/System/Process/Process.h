#pragma once

#include <ArchSpecific/Types.h>
#include <ArchSpecific/Arch.h>
#include <ArchSpecific/MM/MemoryManager.h>
#include <System/KMalloc.h>
#include <LibLunos/DoublyLinkedList.h>

#define PROCESS_STACK_SIZE 2048

enum TaskState {
    WAITING
};

class Process;

class Process : public DoublyLinkedNode<Process> {
    public:
        Process();
        Process(u32 eip);
        
        u32 getAllocatedCpuTicks();
        void setAllocatedCpuTicks(size_t ticks);

        u32 getStackPointer();
        void setStackPointer(u32 stackPointer);
        
        void updateTSS();
        TSS* getTSS();
        void saveTSS(TSS tss);
    private:
        size_t m_allocatedCpuTicks;
        TaskState m_currentTaskState;

        u32 m_stackPointer;

        TSS m_processTSS;
};