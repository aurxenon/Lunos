#pragma once

#include <Drivers/Time/TimeDriver.h>

/*
    Base class for all interval timers
*/
class TimerDriver : public TimeDriver {
    public:
        virtual Driver* initialize_driver() = 0;
        virtual bool deinitialize_driver() = 0;
};