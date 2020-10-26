#pragma once

#include <Drivers/Storage/StorageDriver.h>
#include <Drivers/PCI/PCI.h>

#include <ArchSpecific/MM/InterruptManager.h>
#include <ArchSpecific/MM/PIC.h>

#include <Log/KLog.h>

#define ATA_CHS_DEVSEL     0xA0 //sets obsolete bits (CHS mode)
#define ATA_LBA_DEVSEL     0xE0

//copied straight from PCI IDE tutorial
/*
    ATA Registers
*/
#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

/*
    ATA Statuses
*/
#define ATA_SR_BSY     0x80    // Busy
#define ATA_SR_DRDY    0x40    // Drive ready
#define ATA_SR_DF      0x20    // Drive write fault
#define ATA_SR_DSC     0x10    // Drive seek complete
#define ATA_SR_DRQ     0x08    // Data request ready
#define ATA_SR_CORR    0x04    // Corrected data
#define ATA_SR_IDX     0x02    // Index
#define ATA_SR_ERR     0x01    // Error

/*
    ATA Errors
*/
#define ATA_ER_BBK      0x80    // Bad block
#define ATA_ER_UNC      0x40    // Uncorrectable data
#define ATA_ER_MC       0x20    // Media changed
#define ATA_ER_IDNF     0x10    // ID mark not found
#define ATA_ER_MCR      0x08    // Media change request
#define ATA_ER_ABRT     0x04    // Command aborted
#define ATA_ER_TK0NF    0x02    // Track 0 not found
#define ATA_ER_AMNF     0x01    // No address mark

/*
    ATA Commands
*/
#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define PCI_SUBCLASS_PATA 0x01

#define PATA_BAR0 0x1F0
#define PATA_BAR1 0x3F6
#define PATA_BAR2 0x170
#define PATA_BAR3 0x376

#define PATA_PRIMARY_IRQ   0x0E
#define PATA_SECONDARY_IRQ 0x0F

struct ATADriveInfo {
	u16 flags; //2
	u16 unused1[9]; //18
	char serial[20]; //20
	u16 unused2[3]; //6
	char firmware[8]; //8
	char model[40]; //40
	u16 sectors_per_int;
	u16 unused3;
	u16 capabilities[2];
	u16 unused4[2];
	u16 valid_ext_data;
	u16 unused5[5];
	u16 size_of_rw_mult;
	u32 sectors_28;
	u16 unused6[38];
	u64 sectors_48;
	u16 unused7[152];
} __attribute__((packed));

struct PATAChannel {
    bool selectedDriveID;
};

extern "C" void __asm_Primary_PATA_ISR();
extern "C" void __asm_Secondary_PATA_ISR();
extern "C" void Primary_PATA_IRQ_Handler();
extern "C" void Secondary_PATA_IRQ_Handler();

class PATADriver : public StorageDriver {
    public:
        PATADriver(PCIDriver& pciDriver);
        Driver* initialize_driver();
        bool deinitialize_driver();
        bool detectPATAControllers();
        bool detectPATADisks();
    private:
        u32 m_PATA_BAR4;
        PCIDriver& m_pciDriver;
        PCIDevice m_pataControllers[3];
        size_t m_numPATAControllers;
};

class PATADevice {
    public:
        PATADevice(PATAChannel &pataChannel) : m_channelInfo(pataChannel) {}

        bool init(u16 port, u8 id);

        void handleIRQ();

        void delay();
        void readSectorPIO(uint32_t logicalBlockAddress, uint8_t * buf);

        void interpretDriveStatus(u8 statusRegister);
        void interpretDriveError(u8 errorCode);

        bool isDriveSelected();

        template <typename T>
        void cmdWrite(u16 offset, T value);

        template <typename T>
        T cmdRead(u16 offset);
    private:
        u8 m_deviceID;
        u16 m_baseAddress;
        bool m_receivedInterrupt;
        ATADriveInfo m_driveInfo;
        PATAChannel& m_channelInfo;
};