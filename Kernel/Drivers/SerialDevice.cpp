#include "SerialDevice.h"

void SerialDevice::writeString(const char* format)
{
    for (size_t i = 0; i < sizeof(format); i++)
    {
        writeChar(format[i]);
    }
}

int SerialDevice::isTransmitEmpty()
{
   return ioreadb(COM1_PORT + 5) & 0x20;
}
 
void SerialDevice::writeChar(char c)
{
    while (isTransmitEmpty() == 0) 
    {
        iowriteb(COM1_PORT, (u8)c);
    }
}