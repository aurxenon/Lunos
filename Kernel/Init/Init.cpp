#include <Log/KLog.h>
#include <Drivers/SerialDevice.h>
//#include <LibLunos/Vector.h>
#include <LibLunos/sstream.h>

extern "C" {
    void kmain() {
        KClear();
        klog() << "Hello World!" << " 1 " << " 2 " << " 3 " << 4;
        klog() << 5 << 6 << 7;
        klog() << 99;
        /*Vector<string> strings(3);
        strings[0] = "test ";
        strings[1] = "test1";
        strings[2] = "test2";
        klog() << strings[0] << strings[1] << strings[2];*/
        while (true) {}
    }
}