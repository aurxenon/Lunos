#pragma once

#include <ArchSpecific/Types.h>
#include <ArchSpecific/IO.h>

#include <Drivers/Driver.h>

#include <LibLunos/Vector.h>

#include "pci_ids.h"

#define PCI_MAX_BUSES     256
#define PCI_MAX_DEVICES   32
#define PCI_MAX_FUNCTIONS 8

#define PCI_INVALID_DEVICE 0xFFFF

#define PCI_MULTIFUNCTION 0b10000000

#define PCI_ADDRESS_ENABLE_BIT 0b10000000000000000000000000000000

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

#define PCI_VENDOR_OFFSET     0x00
#define PCI_DEVICE_OFFSET     0x02
#define PCI_COMMAND_OFFSET    0x04
#define PCI_STATUS_OFFSET     0x06
#define PCI_REV_ID_OFFSET     0x08
#define PCI_PROF_IF_OFFSET    0x09
#define PCI_SUBCLASS_OFFSET   0x0A
#define PCI_CLASS_CODE_OFFSET 0x0B
#define PCI_CACHE_OFFSET      0x0C
#define PCI_LATENCY_OFFSET    0x0D
#define PCI_HEADER_OFFSET     0x0E
#define PCI_BIST_OFFSET       0x0F
#define PCI_BAR1_OFFSET       0x10
#define PCI_BAR2_OFFSET       0x14
#define PCI_BAR3_OFFSET       0x18
#define PCI_BAR4_OFFSET       0x1C
#define PCI_BAR5_OFFSET       0x20
#define PCI_BAR6_OFFSET       0x24
#define PCI_CIS_OFFSET        0x28
#define PCI_SUB_VENDOR_OFFSET 0x2C
#define PCI_SUBSYSTEM_OFFSET  0x2E
#define PCI_EXPANSION_OFFSET  0x30
#define PCI_RESERVED1_OFFSET  0x34
#define PCI_RESERVED2_OFFSET  0x38
#define PCI_INT_LINE_OFFSET   0x3C
#define PCI_INT_PIN_OFFSET    0x3D
#define PCI_MIN_GNT_OFFSET    0x3E
#define PCI_MAX_LAT_OFFSET    0x3F

struct PCIDevice {
    u32 bus;
    u32 device;
    u32 function;
    u16 pciDeviceCode;
    u16 pciVendorCode;
    u8 pciClassCode;
};

class PCIDriver : Driver {
    public:
        PCIDriver();
        Driver* initialize_driver();
        bool deinitialize_driver();
    private:
        void enumeratePCIDevices();

        PCIDevice m_pciDevices[40];
        size_t m_numPCIDevices;
};

u8 PCIReadByte(u32 bus, u32 device, u32 function, u32 offset);
void PCIWriteByte (u32 bus, u32 device, u32 function, u32 offset, u8 value); 

u16 PCIReadWord(u32 bus, u32 device, u32 function, u32 offset);
void PCIWriteWord(u32 bus, u32 device, u32 function, u32 offset, u16 value);

u32 PCIReadDword(u32 bus, u32 device, u32 function, u32 offset);
void PCIWriteDword(u32 bus, u32 device, u32 function, u32 offset, u32 value);