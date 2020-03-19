#include <Log/KLog.h>
#include <Drivers/SerialDevice.h>

extern "C" {
    void kmain() {
        KClear();
        klog() << "Hello World!" << " 1 " << " 2 " << " 3 ";
        while (true) {}
    }
}