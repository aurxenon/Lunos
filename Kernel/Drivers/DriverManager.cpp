#include "DriverManager.h"

DriverManager::DriverManager() {
    CMOS cmos = CMOS();
    timespec ts = cmos.readTime();
    klog() << " Seconds: " << ts.ts_sec << " Minutes: " << ts.ts_min <<
        " Hours: " << ts.ts_hour << " Month Day: " << ts.ts_mday;
    //klog() << " Month: " << ts.ts_month << " Year: " << ts.ts_year;
}