#pragma once

#include <ArchSpecific/String.h>
#include <Drivers/VideoConsole.h>

//template<class T>
class kostream {
    public:
        kostream() {}
        kostream(string outputStr) {
            outputString = outputStr;
        }
        kostream(const char* data) {
            outputString = string(data);
        }
        //duplicate for char, unsigned char, short, unsigned short, int, unsigned int, long long, unsigned long, unsigned long long, void*
        kostream write(const char *data);
        kostream write(string data);
        void kostreamPrint();
    private:
        string outputString = "";
};

inline kostream operator<<(kostream kernelStream, string data) {
    kernelStream.write(data);
    return kernelStream;
}
inline kostream operator<<(kostream kernelStream, const char *data) {
    kernelStream.write(data);
    return kernelStream;
}

kostream klog();