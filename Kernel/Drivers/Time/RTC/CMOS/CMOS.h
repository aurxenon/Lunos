#pragma once

#include <Drivers/Time/RTC/RTCDriver.h>

#define CMOS_SECONDS    0x80 | 0
#define CMOS_MINUTES    0x80 | 2
#define CMOS_HOURS      0x80 | 4
#define CMOS_WEEK_DAY   0x80 | 6
#define CMOS_MONTH_DAY  0x80 | 7
#define CMOS_MONTH      0x80 | 8
#define CMOS_YEAR       0x80 | 9
#define CMOS_REGISTER_B 0x80 | 11

#define TIME_OUT_PORT 0x70
#define TIME_IN_PORT  0x71

class CMOS : public RTCDriver {
    public:
        CMOS();
        Driver* initialize_driver();
        bool deinitialize_driver();
        timespec readTime();
        void setTime(timespec ts);
        int readCMOS(int timeType);
    private:
};