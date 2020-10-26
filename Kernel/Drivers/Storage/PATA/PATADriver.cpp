#include "PATADriver.h"

PATAChannel m_primaryChannelInfo;
PATAChannel m_secondaryChannelInfo;

PATADevice primaryParentPATADisk(m_primaryChannelInfo);
PATADevice primaryChildPATADisk(m_primaryChannelInfo);
PATADevice secondaryParentPATADisk(m_secondaryChannelInfo);
PATADevice secondaryChildPATADisk(m_secondaryChannelInfo);

Driver* PATADriver::initialize_driver() {
    return nullptr;
}

bool PATADriver::deinitialize_driver() {
    return true;
}

/*
* PATADriver::PATADriver:
*   Initializes connected PATA drives and loads interrupt routines
* Arguments:
*   pciDriver - instance of loaded PCI driver
* Return:
*/
PATADriver::PATADriver(PCIDriver& pciDriver) : m_pciDriver(pciDriver) {
    m_numPATAControllers = 0;
    detectPATAControllers();
    detectPATADisks();

    //load ISR's for both ATA channels
    AddISR(IRQ_BASE + PATA_PRIMARY_IRQ, &__asm_Primary_PATA_ISR);
    AddISR(IRQ_BASE + PATA_SECONDARY_IRQ, &__asm_Secondary_PATA_ISR);
    LoadIDT();
    
    //enable the PIC to respond to ATA IRQ's
    EnableIRQ(PATA_PRIMARY_IRQ);
    EnableIRQ(PATA_SECONDARY_IRQ);
}

/*
* PATADriver::detectPATAControllers:
*   Detects PATA controllers present on PCI bus
* Arguments:
*   pciDriver - instance of loaded PCI driver
* Return:
*   true
*/
bool PATADriver::detectPATAControllers() {
    u32 pataBus, pataDevice, pataFunction; //lazy, only support initializing one pata pci device right now

    for (size_t i = 0; i < m_pciDriver.getNumPCIDevices(); i++) {
        if (m_pciDriver[i].pciClassCode == PCI_CLASS_MASS_STORAGE && m_pciDriver[i].pciSubclassCode == PCI_SUBCLASS_PATA) {
            m_pataControllers[m_numPATAControllers] = m_pciDriver[i];
            m_numPATAControllers++;
            pataBus = m_pciDriver[i].bus;
            pataDevice = m_pciDriver[i].device;
            pataFunction = m_pciDriver[i].function;
            klog() << " Detected an IDE interface at " << m_pciDriver[i].bus << "," << m_pciDriver[i].device
                 << "," << m_pciDriver[i].function;
        }
    }

    u16 pataPCICommandRegister = PCIReadDword(pataBus, pataDevice, pataFunction, PCI_COMMAND_OFFSET);
    pataPCICommandRegister |= PCI_BUSMASTER_ENABLE_BIT;
    PCIWriteDword(pataBus, pataDevice, pataFunction, PCI_COMMAND_OFFSET, pataPCICommandRegister);

    return true;
}

/*
* PATADriver::detectPATADisks:
*   Attempts to initialize any potentially connected PATA devices
* Arguments:
* Return:
*   true
*/
bool PATADriver::detectPATADisks() {
    primaryParentPATADisk.init(PATA_BAR0, 0);
    primaryChildPATADisk.init(PATA_BAR0, 1);
    secondaryParentPATADisk.init(PATA_BAR2, 2);
    secondaryChildPATADisk.init(PATA_BAR2, 3);

    return true;
}

/*
* Primary_PATA_IRQ_Handler:
*   Calls appropriate interrupt handler for drives on primary channel
* Arguments:
* Return:
*/
extern "C" void Primary_PATA_IRQ_Handler() {
    primaryParentPATADisk.handleIRQ();
    primaryChildPATADisk.handleIRQ();
    EndInterrupt(PATA_PRIMARY_IRQ);
}

/*
* Secondary_PATA_IRQ_Handler:
*   Calls appropriate interrupt handler for drives on secondary channel
* Arguments:
* Return:
*/
extern "C" void Secondary_PATA_IRQ_Handler() {
    secondaryParentPATADisk.handleIRQ();
    secondaryChildPATADisk.handleIRQ();
    EndInterrupt(PATA_SECONDARY_IRQ);
}

/*
* __asm_Primary_PATA_ISR:
*   Lowest level of interrupt chain for primary channel, calls C functions
* Arguments:
* Return:
*/
__asm(
    ".globl __asm_Primary_PATA_ISR\n"
    "__asm_Primary_PATA_ISR:\n"
    "   call Primary_PATA_IRQ_Handler\n"
    "   iret\n"
);

/*
* __asm_Secondary_PATA_ISR:
*   Lowest level of interrupt chain for secondary channel, calls C functions
* Arguments:
* Return:
*/
__asm(
    ".globl __asm_Secondary_PATA_ISR\n"
    "__asm_Secondary_PATA_ISR:\n"
    "   call Secondary_PATA_IRQ_Handler\n"
    "   iret\n"
);