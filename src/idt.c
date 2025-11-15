#include <idt.h>
#include <io.h>

extern void* idtStubTable[];
extern void loadIdt(IDTPtr* i);
__attribute__((aligned(0x10)))
static IDTGate idt[256];

static IDTPtr idtPtr;

void idtSetGate(uint8_t gate, uint32_t offset, uint16_t selector, uint8_t flags) {
    idt[gate].offsetLo = offset & 0xFFFF;
    idt[gate].offsetHi = (offset & 0xFFFF0000) >> 16;
    idt[gate].reserved = 0;
    idt[gate].selector = selector;
    idt[gate].flags = flags;
}

void idtInit() {
    for(int i = 0; i < 32; i++) {
        idtSetGate(i, (uint32_t)idtStubTable[i], 0x08, 0b10001110);
    }
    idtPtr.size = sizeof(idt) - 1;
    idtPtr.offset = (uint32_t)&idt;
    outb(0x11, 0x20);
    outb(0x11, 0xA0);   
    outb(0x20, 0x21);   
    outb(0x28, 0xA1);   
    outb(1 << 2, 0x21);   
    outb(2, 0xA1);   
    outb(1, 0x21);   
    outb(1, 0xA1);   
    outb(0x00, 0x21);
    outb(0x00, 0xA1);
    loadIdt(&idtPtr);
    printf("[x86] initialized idt\n");
}

void mainExceptionHandler(IntFrame* intframe) {
    printf("[except] x86 exception --- vector %d\n", intframe->intno);
    printf("-- EIP: %x\n", intframe->eip);
    __asm__ volatile("cli; hlt");

}