#include "PIC.h"

/*On IMR, IRQ's are disabled by flipping the bit number that corresponds to the IRQ
*number to 1. So for example, if one wanted to disable IRQ 1, bit 1 on the IMR for PIC0
*would be flipped to 1
*/

/*
* DisableIRQ:
*   Disables a specific IRQ, and prevents messages from being raised and sent to the processor
* Arguments:
*   irq - number of the IRQ to be disabled
* Return:
*/
void DisableIRQ(u8 irq)
{
    u8 imr;
    if (irq > 7) {
        imr = ioreadb(PIC1_DATA);
        imr |= 1 << (irq - 8); //reads current mask, disables bit that corresponds to irq number
        iowriteb(PIC1_DATA, imr);
    } else {
        imr = ioreadb(PIC0_DATA);
        imr |= 1 << irq;
        iowriteb(PIC0_DATA, imr);
    }
}

/*
* EnableIRQ:
*   Enables a specific IRQ, and allows messages to be raised and sent to the processor
* Arguments:
*   irq - number of the IRQ to be enabled
* Return:
*/
void EnableIRQ(u8 irq)
{
    u8 imr;
    if (irq > 7) {
        imr = ioreadb(PIC1_DATA) & ~(1 << (irq - 8)); //reads current mask, flips bit of irq to be enabled
        iowriteb(PIC1_DATA, imr);
    } else {
        imr = ioreadb(PIC0_DATA) & ~(1 << irq);
        iowriteb(PIC0_DATA, imr);
    }
}

/*
* EndInterrupt:
*   Sends an EOI message to the PIC and allows the PIC to begin raising interrupts again
* Arguments:
*   irq - number of the IRQ that was received
* Return:
*/
void EndInterrupt(u8 irq)
{
    if (irq > 7) {
        iowriteb(PIC1, PIC_EOI);
        iowriteb(PIC0, PIC_EOI);
    } else {
        iowriteb(PIC0, PIC_EOI);
    }
}

/*
* InitializePIC:
*   Enables the PIC and maps IRQ's to ISR's 64-80
* Arguments:
* Return:
*/
void InitializePIC()
{
    //ICW1 - begins initialization and lets master PIC know there's going to be an ICW4
    iowriteb(PIC0, PIC_INITIALIZE);
    iowriteb(PIC1, PIC_INITIALIZE);

    //ICW2 - tells PIC's where to map IRQ's
    iowriteb(PIC0_DATA, IRQ_BASE);
    iowriteb(PIC1_DATA, IRQ_SLAVE_BASE);

    //ICW3 - sets up master-slave relationship
    iowriteb(PIC0_DATA, PIC_MASTER_ICW3);
    iowriteb(PIC1_DATA, PIC_SLAVE_ICW3);

    //ICW4 - sets up PICs in 8086 mode
    iowriteb(PIC0_DATA, PIC_ICW4);
    iowriteb(PIC1_DATA, PIC_ICW4);

    //send blank masks to both PIC's
    iowriteb(PIC0_DATA, 0x00);
    iowriteb(PIC1_DATA, 0x00);
}