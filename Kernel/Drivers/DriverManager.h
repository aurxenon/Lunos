#pragma once

#include <LibLunos/Vector.h>

#include <Drivers/Time/RTC/CMOS/CMOS.h>

#include <Log/KLog.h>

/*
    Supposed to keep track of and control all device drivers
*/
class DriverManager {
    public:
        DriverManager();
        ~DriverManager();
        bool InitializeDriver(bool*(void));
        bool DeinitializeDriver(bool*(void));
    private:
        //Vector<Driver> m_activeDrivers;
};