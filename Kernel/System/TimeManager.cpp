#include "TimeManager.h"

/*TimeManager::TimeManager() {
    Vector<RTCDriver*> rtcDrivers = Vector<RTCDriver*>();
    Vector<TimerDriver*> timerDrivers = Vector<TimerDriver*>();
}*/

void TimeManager::registerRTC(RTCDriver* rtcDriver) {
    rtcDrivers.push_back(rtcDriver);
}

/*void TimeManager::registerTimer(TimerDriver* timerDriver) {
    timerDrivers.push_back(timerDriver);
}*/

timespec TimeManager::getCurrentTime() {
    return rtcDrivers[0]->readTime();
}