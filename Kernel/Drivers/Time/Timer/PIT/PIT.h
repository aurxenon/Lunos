#pragma once 

#include <Drivers/Time/Timer/TimerDriver.h>
#include <ArchSpecific/MM/PIC.h>
#include <ArchSpecific/MM/InterruptManager.h>
#include <ArchSpecific/IO.h>
#include <ArchSpecific/Arch.h>
#include <System/Scheduler/Scheduler.h>

#define PIT_IRQ      0x00
#define PIT_CHANNEL0 0x40
#define PIT_CMD      0x43

#define PIT_CHANNEL0_SELECT 0x00 //initializes PIT Channel 0
#define PIT_TICKS_ACCESS    0x30 //allows setting the ticks per second by sending low and high bytes
#define PIT_SQUARE_WAVE     0x06 //square wave generator

#define PIT_FREQUENCY    1193182
#define TICKS_PER_SECOND 500

class PIT : public TimerDriver {
    public:
        PIT();
        Driver* initialize_driver();
        bool deinitialize_driver();
        void setFrequency(int ticksPerSecond);
    private:
};