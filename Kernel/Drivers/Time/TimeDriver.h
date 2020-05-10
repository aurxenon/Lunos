#pragma once

#include <Drivers/Driver.h>

/*
    Base class for all time related devices
*/
class TimeDriver : public Driver {
    public:
        virtual Driver* initialize_driver() = 0;
        virtual bool deinitialize_driver() = 0;
};