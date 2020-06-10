#include "PIT.h"

u32 count = 0; //gonna have to be moved to some sort of global timer class

extern "C" void __asm_PIT_ISR();

PIT::PIT() {
    //stub   
}

/*
* PIT::initialize_driver:
*   Initializes the PIT and sets it to fire TICKS_PER_SECOND times per second, also
*   registers the PIT interrupt handler in the IDT
* Arguments:
* Return:
*/
Driver* PIT::initialize_driver() {
    iowriteb(PIT_CMD, PIT_TICKS_ACCESS | PIT_CHANNEL0_SELECT | PIT_SQUARE_WAVE); //enables PIT

    setFrequency(TICKS_PER_SECOND);
    AddISR(IRQ_BASE + PIT_IRQ, &__asm_PIT_ISR);
    LoadIDT();
    EnableIRQ(PIT_IRQ);
    return this;
}

/*
* PIT::setFrequency:
*   Sets how many times a second the PIT should send an IRQ
* Arguments:
*   ticksPerSecond - how many times a second the PIT should fire an interrupt
* Return:
*/
void PIT::setFrequency(int ticksPerSecond) {
    u16 fireInterval = (PIT_FREQUENCY / ticksPerSecond);
    iowriteb(PIT_CHANNEL0, fireInterval & 0xFF); //send low byte
    iowriteb(PIT_CHANNEL0, (fireInterval >> 8) & 0xFF); //send high byte
}

/*
* PIT::deinitializeDriver:
*   Deinitializes the PIT once it's no longer needed
* Arguments:
* Return:
*/
bool PIT::deinitialize_driver() {
    //stub
    return true;
}

/*
* PIT_IRQ_Handler:
*   Updates the global timer and sends the PIC an acknowledgment that the IRQ was handled
* Arguments:
* Return:
*/
extern "C" void PIT_IRQ_Handler() {
    count++;
    klog() << "-PIT-" << count;
    EndInterrupt(PIT_IRQ);
}

/*
* __asm_PIT_ISR:
*   Calls PIT_IRQ_Handler and cleanly exits the ISR once completed
* Arguments:
* Return:
*/
__asm(
    ".globl __asm_PIT_ISR\n"
    "__asm_PIT_ISR:\n"
    "   call PIT_IRQ_Handler\n"
    "   iret\n"
);