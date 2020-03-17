#include <Utils/KLog.h>
#include <Drivers/SerialDevice.h>

extern "C" {
    void kmain() {
        KLog("Hello World!");
        while (true) {}
    }
}