#include <Log/KLog.h>
#include <Drivers/SerialDevice.h>
#include <LibLunos/Vector.h>
#include <LibLunos/sstream.h>
#include <ArchSpecific/MM/MemoryManager.h>
#include <Drivers/DriverManager.h>
#include <ArchSpecific/MM/InterruptManager.h>
#include <ArchSpecific/MM/PIC.h>

extern "C" {
    void kmain() {
        DisableInterrupts();
        KClear();
        klog() << "Hello World!" << " 1 " << " 2 " << " 3 " << 4;
        initializePaging();
        klog() << " Bottom 4MB of RAM identity mapped! ";
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
        EnableInterrupts();
        __asm __volatile__("int $0x0");
        __asm __volatile__("int $0x01");
        __asm __volatile__("int $0x02");
        __asm __volatile__("int $0xee");
        //__asm __volatile__("ud2");
        while (true) {}
    }
}