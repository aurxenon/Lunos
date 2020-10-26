#include "PCI.h"
#include <Log/KLog.h>

/*
* PCIDriver::PCIDriver:
*   Construct a new PCI driver instance
* Arguments:
* Return:
*/
PCIDriver::PCIDriver() {
    m_numPCIDevices = 0;
    enumeratePCIDevices();
    for (size_t i = 0; i < m_numPCIDevices; i++) {
        klog() << "{" << m_pciDevices[i].bus << "," << m_pciDevices[i].device << "," << m_pciDevices[i].function << "," << m_pciDevices[i].pciDeviceCode << "," << m_pciDevices[i].pciVendorCode << "," << m_pciDevices[i].pciClassCode << "}";
    }
}

/*
* PCIDriver::enumeratePCIDevices:
*   Iterate over each bus, device, and function to discover all present PCI devices. Saves
*   all discovered PCI devices in an array
* Arguments:
* Return:
*/
void PCIDriver::enumeratePCIDevices() {
    
    for (u32 bus = 0; bus < PCI_MAX_BUSES; bus++) { //iterate over all buses
        for (u32 device = 0; device < PCI_MAX_DEVICES; device++) { //iterate over all devices
            if (PCIReadWord(bus, device, 0, PCI_VENDOR_OFFSET) != PCI_INVALID_DEVICE) { //check vendor id to discover if device is present

                u16 pciDeviceCode = PCIReadWord(bus, device, 0, PCI_DEVICE_OFFSET);
                u16 pciVendorCode = PCIReadWord(bus, device, 0, PCI_VENDOR_OFFSET);
                u8 pciSubclassCode = PCIReadByte(bus, device, 0, PCI_SUBCLASS_OFFSET);
                u8 pciClassCode = PCIReadByte(bus, device, 0, PCI_CLASS_CODE_OFFSET);
            
                m_pciDevices[m_numPCIDevices] = ((PCIDevice){bus, device, 0, pciDeviceCode, 
                        pciVendorCode, pciSubclassCode, pciClassCode}); //save device if present
                m_numPCIDevices++; //increment number of present PCI devices

                if (PCIReadWord(bus, device, 0, PCI_HEADER_OFFSET) & PCI_MULTIFUNCTION) { //if device has more than 1 function, discover all functions
                    for (u32 function = 1; function < PCI_MAX_FUNCTIONS; function++) {

                        pciDeviceCode = PCIReadWord(bus, device, function, PCI_DEVICE_OFFSET);
                        pciVendorCode = PCIReadWord(bus, device, function, PCI_VENDOR_OFFSET);
                        pciSubclassCode = PCIReadByte(bus, device, function, PCI_SUBCLASS_OFFSET);
                        pciClassCode = PCIReadByte(bus, device, function, PCI_CLASS_CODE_OFFSET);

                        if (PCIReadWord(bus, device, function, PCI_VENDOR_OFFSET) != PCI_INVALID_DEVICE) {
                            m_pciDevices[m_numPCIDevices] = ((PCIDevice){bus, device, function, 
                                    pciDeviceCode, pciVendorCode, pciSubclassCode, pciClassCode}); //save device along with function if present
                            m_numPCIDevices++; //increment number of present PCI devices
                        }
                    }
                }
            }
        }
    }
}

/*
* PCIDriver::initialize_driver:
*   stub
* Arguments:
* Return:
*   null
*/
Driver* PCIDriver::initialize_driver() {
    return nullptr;
}

/*
* PCIDriver::deinitialize_driver:
*   stub
* Arguments:
* Return:
*   true
*/
bool PCIDriver::deinitialize_driver() {
    return true;
}

/*
* PCIDriver::operator[]:
*   Returns information about a PCI device using a specified index
* Arguments:
*   index - the location within the array of PCI devices
* Return:
*   Information about the PCI device at the specified index
*/
PCIDevice PCIDriver::operator[](size_t index) {
    return m_pciDevices[index];
}

/*
* PCIDriver::getNumPCIDevices:
*   Returns the number of PCI devices present
* Arguments:
* Return:
*   The number of PCI devices present within the system
*/
size_t PCIDriver::getNumPCIDevices() {
    return m_numPCIDevices;
}

/*
* FormatConfigAddress:
*   Formats a config address using given PCI device information, and returns it
* Arguments:
*   bus - the bus number of the device to be read from
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be read from
*   offset - the offset within the config space to be read from
* Return:
*   Formatted config address
*/
u32 FormatConfigAddress(u32 bus, u32 device, u32 function, u32 offset) {
    u32 configAddress = PCI_ADDRESS_ENABLE_BIT;
	configAddress |= ((bus & 0xFF) << 16);	// bus #
	configAddress |= ((device & 0x1F) << 11);	// device #
	configAddress |= ((function & 0x07) << 8);	// func #
	configAddress |= ((offset & 0xff));
    
    return configAddress;
}

/*
* PCIReadByte:
*   Reads a single unsigned 8 bit value from a specified PCI device's config space at the given offset
* Arguments:
*   bus - the bus number of the device to be read from
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be read from
*   offset - the offset within the config space to be read from
* Return:
*   Unsigned 8 bit value at the specified configuration space offset
*/
u8 PCIReadByte(u32 bus, u32 device, u32 function, u32 offset)
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));
	return ioreadb(PCI_CONFIG_DATA + (offset & 3));
}

/*
* PCIWriteByte:
*   Writes a single unsigned 8 bit value to a specified PCI device's config space at the given offset
* Arguments:
*   bus - the bus number of the device to be written to
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be written to
*   offset - the offset within the config space to be written to
*   value - the value to be written at the specified offset
* Return:
*/
void PCIWriteByte (u32 bus, u32 device, u32 function, u32 offset, u8 value)
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));
	iowriteb(PCI_CONFIG_DATA + (offset & 3), value);
}

/*
* PCIReadWord:
*   Reads a single unsigned 16 bit value from a specified PCI device's config space at the given offset
* Arguments:
*   bus - the bus number of the device to be read from
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be read from
*   offset - the offset within the config space to be read from
* Return:
*   Unsigned 16 bit value at the specified configuration space offset
*/
u16 PCIReadWord(u32 bus, u32 device, u32 function, u32 offset)
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));
	return ioreadw(PCI_CONFIG_DATA + (offset & 1));
}

/*
* PCIWriteWord:
*   Writes a single unsigned 16 bit value to a specified PCI device's config space at the given offset
* Arguments:
*   bus - the bus number of the device to be written to
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be written to
*   offset - the offset within the config space to be written to
*   value - the value to be written at the specified offset
* Return:
*/
void PCIWriteWord(u32 bus, u32 device, u32 function, u32 offset, u16 value)
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));
	iowritew(PCI_CONFIG_DATA + (offset & 1), value);
}

u32 PCIReadDword(u32 bus, u32 device, u32 function, u32 offset)
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));
	return ioreaddw(PCI_CONFIG_DATA);
}

/*
* PCIWriteDword:
*   Writes a single unsigned 32 bit value to a specified PCI device's config space at the given offset
* Arguments:
*   bus - the bus number of the device to be written to
*   device - the device number on the specific bus the device is located on
*   function - the specific function of the device to be written to
*   offset - the offset within the config space to be written to
*   value - the value to be written at the specified offset
* Return:
*/
void PCIWriteDword(u32 bus, u32 device, u32 function, u32 offset, u32 value) 
{
	iowritedw(PCI_CONFIG_ADDRESS, FormatConfigAddress(bus, device, function, offset));	
	iowritedw(PCI_CONFIG_DATA, value);
}