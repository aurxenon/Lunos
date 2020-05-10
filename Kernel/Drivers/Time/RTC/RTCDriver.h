#pragma once

#include <Drivers/Time/TimeDriver.h>

struct timespec {
    int ts_sec;
    int ts_min;
    int ts_hour;
    int ts_mday;
    int ts_month;
    int ts_year;
    int ts_wday;
};

/*
    Base class for all Real Time Clock drivers
*/
class RTCDriver : public TimeDriver {
    public:
        virtual Driver* initialize_driver() = 0;
        virtual bool deinitialize_driver() = 0;
        virtual timespec readTime(void) = 0;
        virtual void setTime(timespec ts) = 0;
    private:
};