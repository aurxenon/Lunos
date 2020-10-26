#include "PATADriver.h"

/*
* PATADevice::init:
*   Initializes connected PATA drives and loads interrupt routines, grabs drive information
* Arguments:
*   port - the IO port that's used to interface with the drive
*   id - the drive number, can be between 0 and 3
* Return:
*   bool - true if successful initialization, false if unsuccessful initialization
*/
bool PATADevice::init(u16 port, u8 id) {
    m_baseAddress = port;
    m_deviceID = id;

    m_channelInfo.selectedDriveID = m_deviceID; //change the currently selected drive on this channel

    cmdWrite<u8>(ATA_REG_HDDEVSEL, ATA_LBA_DEVSEL | ((m_deviceID % 2) << 4)); //actually select it
    cmdWrite<u8>(ATA_REG_SECCOUNT0, 0x00);
    cmdWrite<u8>(ATA_REG_LBA0, 0x00);
    cmdWrite<u8>(ATA_REG_LBA1, 0x00);
    cmdWrite<u8>(ATA_REG_LBA2, 0x00);

    if (cmdRead<u8>(ATA_REG_STATUS) == 0x00) { //if the device can't be probed, it's not there
        klog() << " No ATA Disk detected at id:" << (int)id;
        return false;
    }

    cmdWrite<u8>(ATA_REG_COMMAND, ATA_CMD_IDENTIFY); //request the drive spec string

    while (cmdRead<u8>(ATA_REG_STATUS) & ATA_SR_BSY) {} //wait for the drive to respond

    u16* diskInfoBuffer = (u16*)(&m_driveInfo);

    for (int i = 0; i < 256; i++) {
		diskInfoBuffer[i] = cmdRead<u16>(ATA_REG_DATA); //read in the drive spec string
	}

    u8* ptr = (u8 *)&m_driveInfo.model;
	for (int i = 0; i < 39; i+=2) { //the drive names have every other character switched
		uint8_t tmp = ptr[i+1]; //so lets switch them back
		ptr[i+1] = ptr[i];
		ptr[i] = tmp;
	}

    klog() << " ATA ID: " << (int)m_deviceID << " Device Name " << m_driveInfo.model;

    return true;
}

/*
* PATADevice::handleIRQ:
*   Handles any IRQ's fired by the drive, lets other code know an IRQ has occurred
* Arguments:
* Return:
*/
void PATADevice::handleIRQ() {
    m_receivedInterrupt = true;
    
    return;
}

/*
* PATADevice::delay:
*   Reads ALTSTATUS port 4 times to give drive 400ns to respond
* Arguments:
* Return:
*/
void PATADevice::delay() {
    for (int i = 0; i < 4; i++) {
        cmdRead<u8>(ATA_REG_ALTSTATUS);
    }
}

/*
* PATADevice::readSectorPIO:
*   Reads a disk sector into a buffer, uses PIO mode
* Arguments:
*   logicalBlockAddress - the LBA of the sector to be read
*   buf - the buffer that's to be read into
* Return:
*/
void PATADevice::readSectorPIO(uint32_t logicalBlockAddress, uint8_t * buf) {
    DisableInterrupts(); //disable interrupts to avoid having multiple threads reading from disk
    while (cmdRead<u8>(ATA_REG_STATUS) & ATA_SR_BSY) {} //wait for drive to become responsive

    if (!isDriveSelected()) { //if the drive isn't selected, select it
        cmdWrite<u8>(ATA_REG_HDDEVSEL, ATA_LBA_DEVSEL | (m_deviceID % 2) << 4 | (logicalBlockAddress & 0x0f000000) >> 24);
        m_channelInfo.selectedDriveID = m_deviceID;
    }
    
    delay(); //gotta give that 400ns delay to ensure drive is selected

    cmdWrite<u8>(ATA_REG_CONTROL, 0); //make sure drive interrupts are enabled

    cmdWrite<u8>(ATA_REG_SECCOUNT0, 1); //we're only reading 1 sector
    cmdWrite<u8>(ATA_REG_LBA0, (logicalBlockAddress & 0x000000ff) >> 0); //write each part of the LBA
    cmdWrite<u8>(ATA_REG_LBA1, (logicalBlockAddress & 0x0000ff00) >> 8);
    cmdWrite<u8>(ATA_REG_LBA2, (logicalBlockAddress & 0x00ff0000) >> 16);

    cmdWrite<u8>(ATA_REG_COMMAND, ATA_CMD_READ_PIO); //no dma mode for us today

    EnableInterrupts(); //enable interrupts so we can know when to read our data
    
    while (!m_receivedInterrupt) {
        u8 altStatusRegister = cmdRead<u8>(ATA_REG_ALTSTATUS);
        if (altStatusRegister & ATA_SR_ERR) { //if an error occurs, we leave
            u8 errorRegister = cmdRead<u8>(ATA_REG_ERROR);
            interpretDriveError(errorRegister);
            return;
        }
    }
    
    DisableInterrupts(); //we got our interrupt, now we can attempt to read
    m_receivedInterrupt = false;

    u8 currentStatus = cmdRead<u8>(ATA_REG_STATUS); //check drive status

    while ((currentStatus & ATA_SR_BSY) && isDriveSelected()) { //if it's busy, we wait
        currentStatus = cmdRead<u8>(ATA_REG_STATUS);
    }

    if ((currentStatus & ATA_SR_DRQ) && isDriveSelected()) { //if it's ready to read, we read
        u16* convBuffer = (u16*)buf;
        
        for (int i = 0; i < 256; i++) {
            convBuffer[i] = cmdRead<u16>(ATA_REG_DATA);
        }
    } else if (isDriveSelected()){ //otherwise we check the drive status and then leave
        interpretDriveStatus(currentStatus);
    }

    EnableInterrupts(); //reenable interrupts so other parts of the system can function
}

/*
* PATADevice::interpretDriveStatus:
*   Converts drive status code into a human readable version
* Arguments:
*   statusRegister - contains the drive status code to be interpreted
* Return:
*/
void PATADevice::interpretDriveStatus(u8 statusRegister) {
    if (statusRegister & ATA_SR_BSY) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_BSY";
    }
    if (statusRegister & ATA_SR_DRDY) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_DRDY";
    }
    if (statusRegister & ATA_SR_DF) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_DF";
    }
    if (statusRegister & ATA_SR_DSC) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_DSC";
    }
    if (statusRegister & ATA_SR_DRQ) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_DRQ";
    }
    if (statusRegister & ATA_SR_CORR) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_CORR";
    }
    if (statusRegister & ATA_SR_IDX) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_IDX";
    }
    if (statusRegister & ATA_SR_ERR) {
        klog() << " Drive: " << m_deviceID << " is ATA_SR_ERR";
    }
}

/*
* PATADevice::interpretDriveError:
*   Converts the drive error code into something human readable
* Arguments:
*   errorCode - the error code to be converted
* Return:
*/
void PATADevice::interpretDriveError(u8 errorCode) {
    if (errorCode & ATA_ER_BBK) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_BBK";
    }
    if (errorCode & ATA_ER_UNC) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_UNC";
    }
    if (errorCode & ATA_ER_MC) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_MC";
    }
    if (errorCode & ATA_ER_IDNF) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_IDNF";
    }
    if (errorCode & ATA_ER_MCR) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_MCR";
    }
    if (errorCode & ATA_ER_ABRT) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_ABRT";
    }
    if (errorCode & ATA_ER_TK0NF) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_TK0NF";
    }
    if (errorCode & ATA_ER_AMNF) {
        klog() << " Drive: " << m_deviceID << " Error: ATA_ER_AMNF";
    }
}

/*
* PATADevice::isDriveSelected:
*   Returns whether or not the drive is currently selected on the PATA channel
* Arguments:
* Return:
*   bool - true if selected, false if not selected
*/
bool PATADevice::isDriveSelected() {
    return m_channelInfo.selectedDriveID == m_deviceID;
}

/*
* PATADevice::cmdWrite:
*  Allows writing to drive registers
* Arguments:
*   offset - the offset of the drive register to write to
*   value - what is to be written to the drive register
* Return:
*/
template <typename T>
void PATADevice::cmdWrite(u16 offset, T value) {
    if (sizeof(value) == 1) {
        iowriteb(m_baseAddress + offset, value);
    } else if (sizeof(value) == 2) {
        iowritew(m_baseAddress + offset, value);
    } else if (sizeof(value) == 4) {
        iowritedw(m_baseAddress + offset, value);
    }
}

/*
* PATADevice::cmdRead:
*   Allows reading from drive registers
* Arguments:
*   offset - the offset of the drive register to read from
* Return:
*   T - value contained in drive register
*/
template <typename T>
T PATADevice::cmdRead(u16 offset) {
    if (sizeof(T) == 1) {
        return ioreadb(m_baseAddress + offset);
    } else if (sizeof(T) == 2) {
        return ioreadw(m_baseAddress + offset);
    } else if (sizeof(T) == 4) {
        return ioreaddw(m_baseAddress + offset);
    }
}