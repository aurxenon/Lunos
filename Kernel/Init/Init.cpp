#include <Log/KLog.h>
#include <Drivers/SerialDevice.h>
#include <LibStandard/Vector.h>
#include <LibStandard/sstream.h>
#include <ArchSpecific/MM/MemoryManager.h>
#include <ArchSpecific/MM/GDT.h>
#include <Drivers/DriverManager.h>
#include <ArchSpecific/MM/InterruptManager.h>
#include <ArchSpecific/MM/PIC.h>
#include <Drivers/Time/Timer/PIT/PIT.h>
#include <System/Scheduler/Scheduler.h>
#include <Drivers/PCI/PCI.h>
#include <Drivers/Storage/PATA/PATADriver.h>
#include <ArchSpecific/multiboot.h>

void process1() {
    while (true) {
        //klog() << " Testing1 ";
        EnableInterrupts();
        asm("hlt");
    }
}

void process2() {
    while (true) {
        //klog() << " Testing2 ";
        asm("hlt");
    }
}

extern "C" {
    void kmain(void* kernelPageArea, multiboot_info_t* mbd, unsigned int magic) {
        DisableInterrupts();
        set_iopl();
        KClear();
        klog() << "Hello World!" << " 1 " << " 2 " << " 3 " << 4;
        MemoryManager memoryManager(kernelPageArea, mbd);
        InitializeSegmentation();
        klog() << "GDT initialized! ";
        InitializeInterrupts();
        klog() << "Interrupts enabled! ";
        InitializePIC();
        klog() << "PIC enabled! ";
        klog() << 5 << 6 << 7;
        klog() << 99;
        Vector<int> nums(3);
        nums[0] = 9;
        nums[1] = 8;
        nums[2] = 7;
        klog() << " Vector Test:" << nums[0] << "-" << nums[1]  << "-" << nums[2];
        //i'm pretty sure i was using this to check and see if KPrintString
        //was smart enough to go onto the next line once the row was filled up
        klog() << "increment increment increment increment increment";
        DriverManager driverManager = DriverManager();

        for (int i = 0; i <= 16; i++) {
            DisableIRQ(i);
        }
        EnableIRQ(2);

        PIT pitDriver = PIT();
        pitDriver.initialize_driver();
        PCIDriver pciDriver = PCIDriver();
        PATADriver pataDriver = PATADriver(pciDriver);
        EnableInterrupts();
        extern PATADevice primaryParentPATADisk;
        //KClear();
        char buffer[512];
        primaryParentPATADisk.readSectorPIO(0, (u8*)buffer);
        klog() << buffer;
        //primaryParentPATADisk.readSectorPIO(1, (u8*)buffer);
        //klog() << buffer;
        /*__asm __volatile__("int $0x0");
        __asm __volatile__("int $0x01");
        __asm __volatile__("int $0x02");*/
        //__asm __volatile__("int $0xee");
        //__asm __volatile__("ud2");
        while (true) {
            //klog() << "K1";
            asm("hlt");
        }
    }
}