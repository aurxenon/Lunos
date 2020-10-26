#pragma once

#include <Drivers/Driver.h>

#define PCI_CLASS_MASS_STORAGE 0x01

/*
    Base class for all storage related devices
*/
class StorageDriver : public Driver {
    public:
        virtual Driver* initialize_driver() = 0;
        virtual bool deinitialize_driver() = 0;
};