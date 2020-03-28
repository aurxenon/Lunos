#include <Log/KLog.h>
#include <Drivers/SerialDevice.h>
#include <LibLunos/Vector.h>
#include <LibLunos/sstream.h>

extern "C" {
    void kmain() {
        KClear();
        klog() << "Hello World!" << " 1 " << " 2 " << " 3 " << 4;
        klog() << 5 << 6 << 7;
        klog() << 99;
        Vector<int> nums(3);
        nums[0] = 9;
        nums[1] = 8;
        nums[2] = 7;
        klog() << " Vector Test:" << nums[0] << "-" << nums[1]  << "-" << nums[2];
        klog() << "increment increment increment increment increment";
        while (true) {}
    }
}