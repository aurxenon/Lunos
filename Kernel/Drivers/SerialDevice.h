#pragma once

#include <ArchSpecific/IO.h>
#include <ArchSpecific/String.h>
#include <ArchSpecific/Types.h>

#define COM1_PORT 0x3f8

/*FIXME: LITERALLY BROKEN LMOA*/
class SerialDevice {
    public:
        SerialDevice() {
            iowriteb(COM1_PORT + 1, 0x00);    // Disable all interrupts
            iowriteb(COM1_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
            iowriteb(COM1_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
            iowriteb(COM1_PORT + 1, 0x00);    //                  (hi byte)
            iowriteb(COM1_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
            iowriteb(COM1_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
            iowriteb(COM1_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
        };
        void writeString(const char* format);
        void writeChar(char c);
    private:
        int isTransmitEmpty();
};