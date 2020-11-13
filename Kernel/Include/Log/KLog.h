#pragma once

#include <ArchSpecific/String.h>
#include <Drivers/VideoConsole.h>
#include <LibStandard/sstream.h>

//FIXME: implement a base stream class for both sstream and kostream
//template<class T>
class kostream {
    public:
        kostream() {
            //outputString = "";
        }
        kostream(string outputStr) {
            outputString = outputStr;
        }
        kostream(const char* data) {
            outputString = string(data);
        }
        //duplicate for char, unsigned char, short, unsigned short, int, unsigned int, long long, unsigned long, unsigned long long, void*
        kostream write(const char *data);
        kostream write(string data);
        void str(string newString);
        void kostreamPrint();
    private:
        string outputString;
};

inline kostream operator<<(kostream kernelStream, string data) {
    kernelStream.write(data);
    return kernelStream;
}
inline kostream operator<<(kostream kernelStream, const char *data) {
    kernelStream.write(data);
    return kernelStream;
}

inline kostream operator<<(kostream kernelStream, int data) {
    //the basic_string implementation is broken right now, so it can only safely print using the cstring implementation of write
    kernelStream.write(to_string(data).c_str());
    return kernelStream;
}

kostream klog();