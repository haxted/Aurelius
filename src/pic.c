#include <pic.h>

void setIrqMask(uint8_t line) {
    uint8_t val = 0;
    if(line < 8) {
        val = inb(0x21) | (1 << line);
        outb(val, 0x21);
        return;
    } else {
        line -= 8;
        val = inb(0xA1) | (1 << line);
        outb(val, 0xA1);
        return;
    }
}

void picSendEoi(uint8_t irq) {
    if(irq < 8) {
        outb(0x20, 0x20);
        return;
    } else {
        outb(0x20, 0xA0);
    }
}

