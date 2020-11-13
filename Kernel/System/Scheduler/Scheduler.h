#pragma once

#include <ArchSpecific/Types.h>
#include <System/Process/Process.h>
#include <LibStandard/DoublyLinkedList.h>
#include <ArchSpecific/Arch.h>
#include <Log/KLog.h>
#include <ArchSpecific/MM/InterruptManager.h>
#include <LibStandard/new.h>

class Scheduler {
    public:
        Scheduler();
        u32 Schedule(u32 esp);
        void addProcess(void processEntryFunction(void));
    private:
        DoublyLinkedList<Process> m_processes;
        Process* m_current;
        bool m_firstTime;
};