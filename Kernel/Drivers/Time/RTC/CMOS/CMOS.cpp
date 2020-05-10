#include "CMOS.h"

#include <ArchSpecific/IO.h>

CMOS::CMOS() {
    //stub
}

Driver* CMOS::initialize_driver() {
    return nullptr;    
}

bool CMOS::deinitialize_driver() {
    return true; //stub
}

timespec CMOS::readTime() {
    //
    //fill time struct with, well, time
    //
    timespec ts = {readCMOS(CMOS_SECONDS), readCMOS(CMOS_MINUTES), readCMOS(CMOS_HOURS),
        readCMOS(CMOS_MONTH_DAY), readCMOS(CMOS_MONTH), readCMOS(CMOS_YEAR), readCMOS(CMOS_WEEK_DAY)};
    return ts;
}

void CMOS::setTime(timespec ts) {
    //stub
}

int CMOS::readCMOS(int timeType) {
    //
    //grab time from CMOS registers
    //
    iowriteb(TIME_OUT_PORT, timeType);
    int value = ioreadb(TIME_IN_PORT);

    //
    //check if data is BCD encoded, if it is, convert it to decimal
    //
    iowriteb(TIME_OUT_PORT, CMOS_REGISTER_B);
    if (!(ioreadb(TIME_IN_PORT) & 0x04)) {
        value = ((value) & 15) + ((value) / 16) * 10;
    }
    return value;
}