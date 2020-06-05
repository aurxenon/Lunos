#include "InterruptManager.h"

const char* interruptDescriptions[17] = {"Divide Error", "Debug", "NMI Interrupt", "Breakpoint", "Overflow",
    "BOUND Range Exceeded", "Invalid Opcode", "Device Not Available", "Double Fault", "CoProcessor Segment Overrun", 
    "Invalid TSS", "Segment Not Present", "Stack Segment Fault", "General Protection", "Page Fault", 
    "Reserved", "Floating-Point Error"};

static IDTPtr interruptTablePtr;
static IDTEntry* interruptTable;

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
Exception(14)
Exception(15)
Exception(16)

/*
* UnimplementedISR:
*   Serves as a blank ISR for interrupt table entries that aren't
*   directly mapped to a dedicated ISR
* Arguments:
* Return:
*/
static void UnimplementedISR()
{
    klog() << " Unimplemented ISR ";
}

/*
* AddISR:
*   Creates an IDT entry that references a specific ISR, thus when an interrupt happens
*   the processor knows which and where the ISR is located
* Arguments:
*   index - integer corresponding to where in the IDT the ISR should be placed
*   ISR - function pointer to the ISR being referenced
* Return:
*/
static void AddISR(int index, void (*ISR)())
{
    interruptTable[index].offset_1 = (((u32)ISR) & 0xffff);
    interruptTable[index].selector = KERNEL_MODE_SELECTOR;
    interruptTable[index].zero = 0;
    interruptTable[index].type_attr = KERNEL_MODE_TYPE_ATTR;
    interruptTable[index].offset_2 = ((((u32)ISR) >> 16) & 0xffff);
}

/*
* LoadIDT:
*   Loads the IDT array into the processor
* Arguments:
* Return:
*/
static inline void LoadIDT()
{
    __asm __volatile__("lidt %0"::"m"(interruptTablePtr));
}

/*
* InitializeInterrupts:
*   Creates IDT array and also initializes each ISR
* Arguments:
* Return:
*/
void InitializeInterrupts()
{
    interruptTable = (IDTEntry*)kmalloce(sizeof(IDTEntry) * IDT_NUM_ENTRIES);

    interruptTablePtr.address = interruptTable;
    interruptTablePtr.size = IDT_NUM_ENTRIES * sizeof(IDTEntry);

    for (int i = 17; i <= (IDT_NUM_ENTRIES - 1); i++) {
        AddISR(i, UnimplementedISR);
    }

    AddISR(0, ExceptionHandler0);
    AddISR(1, ExceptionHandler1);
    AddISR(2, ExceptionHandler2);
    AddISR(3, ExceptionHandler3);
    AddISR(4, ExceptionHandler4);
    AddISR(5, ExceptionHandler5);
    AddISR(6, ExceptionHandler6);
    AddISR(7, ExceptionHandler7);
    AddISR(8, ExceptionHandler8);
    AddISR(9, ExceptionHandler9);
    AddISR(10, ExceptionHandler10);
    AddISR(11, ExceptionHandler11);
    AddISR(12, ExceptionHandler12);
    AddISR(13, ExceptionHandler13);
    AddISR(14, ExceptionHandler14);
    AddISR(15, ExceptionHandler15);
    AddISR(16, ExceptionHandler16);

    LoadIDT();
}