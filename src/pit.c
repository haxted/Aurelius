#include <pit.h>
#include <io.h>
#include <idt.h>
int pitLock = 0;

extern void _irq0Handler();

void initPit() {
    idtSetGate(0x20, (uintptr_t)_irq0Handler, 0x08, 0x8E);
    printf("[pit] initialized pit\n");
}

void pitStartCounter(uint16_t count) {
    outb(0b00110110, MODE_CMD_REG);
    outb((count & 0xFF), CHANNEL0_DAT);
    outb((count >> 8) & 0xFF, CHANNEL0_DAT);
    pitLock = 1;
}

void irq0Handler() {
    if(pitLock) {
        printf("irq 0!\n");
    }
    outb(0x20, 0x20);
}