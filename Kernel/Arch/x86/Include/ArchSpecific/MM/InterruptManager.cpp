#include "InterruptManager.h"

const char* interruptDescriptions[17] = {"Divide Error", "Debug", "NMI Interrupt", "Breakpoint", "Overflow",
    "BOUND Range Exceeded", "Invalid Opcode", "Device Not Available", "Double Fault", "CoProcessor Segment Overrun", 
    "Invalid TSS", "Segment Not Present", "Stack Segment Fault", "General Protection", "Page Fault", 
    "Reserved", "Floating-Point Error"};

IDTPtr interruptTablePtr;
static IDTEntry interruptTable[sizeof(IDTEntry) * IDT_NUM_ENTRIES];

Exception(0)
Exception(1)
Exception(2)
Exception(3)
Exception(4)
Exception(5)
Exception(6)
Exception(7)
Exception(8)
Exception(9)
Exception(10)
Exception(11)
Exception(12)
Exception(13)
Exception(16)

/*
* __asm_UnimplementedISR:
*   Serves as a "safe" assembly wrapper for UnimplementedISR so that the interrupt handler
*   will be safely called
* Arguments:
* Return:
*/
extern "C" void __asm_UnimplementedISR();
__asm(
    ".globl __asm_UnimplementedISR\n"
    "__asm_UnimplementedISR:\n"
    "   call UnimplementedISR\n"
    "   iret\n"
);

/*
* UnimplementedISR:
*   Serves as a blank ISR for interrupt table entries that aren't
*   directly mapped to a dedicated ISR
* Arguments:
* Return:
*/
extern "C" void UnimplementedISR()
{
    klog() << " Unimplemented ISR ";
}

/*
* PageFaultHandler:
*   Error handling when a page fault occurs
* Arguments:
* Return:
*/
extern "C" void PageFaultHandler() {
    klog() << "Caught Page Fault when attempting to access " << read_cr2();
    while(true) {
        asm("nop");
    }
}

/*
* __asm_Exception_ISR14:
*   Serves as a "safe" assembly wrapper for PageFaultHandler so that the interrupt handler
*   will be safely called
* Arguments:
* Return:
*/
extern "C" void __asm_Exception_ISR14();
__asm( \
    ".globl __asm_Exception_ISR14\n"
    "__asm_Exception_ISR14:\n"
    "   call PageFaultHandler\n"
    "   iret\n"
);

/*
* AddISR:
*   Creates an IDT entry that references a specific ISR, thus when an interrupt happens
*   the processor knows which and where the ISR is located
* Arguments:
*   index - integer corresponding to where in the IDT the ISR should be placed
*   ISR - function pointer to the ISR being referenced
* Return:
*/
void AddISR(int index, void (*ISR)())
{
    interruptTable[index].offset_1 = (((u32)ISR) & 0xffff);
    interruptTable[index].selector = KERNEL_MODE_SELECTOR;
    interruptTable[index].zero = 0;
    interruptTable[index].type_attr = KERNEL_MODE_TYPE_ATTR;
    interruptTable[index].offset_2 = ((((u32)ISR) >> 16) & 0xffff);
}

/*
* InitializeInterrupts:
*   Creates IDT array and also initializes each ISR
* Arguments:
* Return:
*/
void InitializeInterrupts()
{
    //interruptTable = (IDTEntry*)kmalloce();

    interruptTablePtr.address = interruptTable;
    interruptTablePtr.size = IDT_NUM_ENTRIES * sizeof(IDTEntry);

    for (int i = 17; i <= (IDT_NUM_ENTRIES - 1); i++) {
        AddISR(i, __asm_UnimplementedISR);
    }

    AddISR(0, __asm_Exception_ISR0);
    AddISR(1, __asm_Exception_ISR1);
    AddISR(2, __asm_Exception_ISR2);
    AddISR(3, __asm_Exception_ISR3);
    AddISR(4, __asm_Exception_ISR4);
    AddISR(5, __asm_Exception_ISR5);
    AddISR(6, __asm_Exception_ISR6);
    AddISR(7, __asm_Exception_ISR7);
    AddISR(8, __asm_Exception_ISR8);
    AddISR(9, __asm_Exception_ISR9);
    AddISR(10, __asm_Exception_ISR10);
    AddISR(11, __asm_Exception_ISR11);
    AddISR(12, __asm_Exception_ISR12);
    AddISR(13, __asm_Exception_ISR13);
    AddISR(14, __asm_Exception_ISR14);
    AddISR(16, __asm_Exception_ISR16);

    LoadIDT();
}