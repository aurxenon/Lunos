#pragma once

#include <LibLunos/bastring.h>

/*
    Base class for all device drivers
*/
//this class is going to be VERY subject to change
class Driver {
    public:
        //sort of like a factory for driver objects
        virtual Driver* initialize_driver() = 0;
        virtual bool deinitialize_driver() = 0;
    private:
        string m_deviceName;
};