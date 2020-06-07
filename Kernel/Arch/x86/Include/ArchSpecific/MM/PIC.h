#pragma once

#include <ArchSpecific/Types.h>
#include <ArchSpecific/IO.h>

#define IRQ_BASE 64
#define IRQ_SLAVE_BASE IRQ_BASE + 0x08

#define PIC0            0x20
#define PIC0_DATA       0x21
#define PIC1            0xA0
#define PIC1_DATA       0xA1

#define PIC_EOI         0x20
#define PIC_INITIALIZE  0x11 
#define PIC_ICW2        IRQ_BASE
#define PIC_MASTER_ICW3 0x04 //ICW3 is a bit field, bit 2 tells the master PIC there's a slave on IRQ2
#define PIC_SLAVE_ICW3  0x02 //tells slave PIC it's connected to master PIC's IRQ2
#define PIC_ICW4        0x01 //8086 mode

void EnableIRQ(u8 irq);
void DisableIRQ(u8 irq);
void EndInterrupt(u8 irq);
void InitializePIC();