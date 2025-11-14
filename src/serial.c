#include <serial.h>
#include <io.h>
#include <stdio.h>
int serialFaulty = 0;
#define CHECK_FLTY() if(serialFaulty) return;
int serialReady = 0;
void initSerial(void) {
    outb(0, COM1+1);
    outb(0x80, COM1+3);
    outb(0x03, COM1);
    outb(0, COM1+1);
    outb(0x03, COM1+3);
    outb(0xC7, COM1+2);
    outb(0x0B, COM1+4);
    outb(0x1E, COM1+4);
    outb(0xAE, COM1);

    if(inb(COM1) != 0xAE) {
        serialFaulty = 1;
        printf("[drv] serial is faulty or does not exist\n");
        return;
    }
    outb(0x0F, COM1+4);
    printf("[drv] initialized serial\n");
    serialReady = 1;
}

void serialPutChar(char c) {
    CHECK_FLTY();
    // while(!(inb(COM1+5) & 0x20));
    outb(c, COM1);
}

void serialPutStr(const char* str) {
    CHECK_FLTY();
    while(*str) {
        serialPutChar(*str);
        str++;
    }
}

