#pragma once

#include <LibLunos/Vector.h>

#include <Drivers/Time/RTC/RTCDriver.h>
#include <Drivers/Time/Timer/TimerDriver.h>

/*
    Supposed to be an easy place for the kernel to retrieve time informaton from
*/
class TimeManager{
    public:
        TimeManager();
        void registerRTC(RTCDriver* rtcDriver);
        //void registerTimer(TimerDriver* timerDriver);
        timespec getCurrentTime();
    private:
        Vector<RTCDriver*> rtcDrivers;
        //Vector<TimerDriver*> timerDrivers;
};

TimeManager TIME_MANAGER = TimeManager(); //not the most object oriented way of doing this