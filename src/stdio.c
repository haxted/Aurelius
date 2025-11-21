#include <stdio.h>
#include <stddef.h>
#include <io.h>
#include <string.h>
#include <serial.h>

volatile char* vgaBuf = (volatile char*)0xb8000;
int col = 0;
int row = 0;
uint8_t currentColor = 0x07;

void updateCursor(int x, int y) {
    uint16_t pos = (y * VGA_WID + x);
    outb(0x0F, 0x3d4);
    outb((uint8_t)pos & 0xFF, 0x3D5);
    outb(0x0E, 0x3D4);
    outb((uint8_t)(pos >> 8) & 0xFF, 0x3D5);
}

void scroll(void) {
    for(int i = 0; i < VGA_WID; i++) {
        vgaBuf[i * 2] = ' ';
        vgaBuf[i * 2 +1] = currentColor;
    }
    for(int y = 1; y < VGA_HEI; y++) {
        for(int x = 0; x < VGA_WID; x++) {
          vgaBuf[(y - 1) * VGA_WID + x] = vgaBuf[y * VGA_WID + x]; 
        }
    }
    for(int i = (VGA_WID * VGA_HEI) - 80; i < (VGA_WID * VGA_HEI); i++) {
        vgaBuf[i * 2] = ' ';
        vgaBuf[i * 2 + 1] = currentColor;
    }
    row = VGA_HEI - 1;
}

void putchar(char c) {
    switch(c) {
        case '\n': {
            row++;
            col = 0;
            return;
        }
        default: break;
    }
    if(col >= VGA_WID) row++;
    if(row >= VGA_HEI) {
        scroll();
    }
    int off = (row * VGA_WID + col);
    vgaBuf[off * 2] = c;
    vgaBuf[off * 2 + 1] = currentColor;
    col++;
    updateCursor(col, row);
}

void putHex(int hex, int set, char* out) {
    if(!out)
        return;
    const char* hexDigits = set ? "0123456789ABCDEF" : "0123456789abcdef";
    for(int i = 0; i < 8; i++) {
        uint8_t nib = (hex >> (28 - i * 4)) & 0xf;
        char dig = hexDigits[nib];
        out[i] = dig;
    }
    out[8] = '\0';
}

void putDec(int dec, char* out) {
    if(!out)
        return;
    int i = 0;
    int neg = 0;
    if(dec < 0) {
        neg = 1;
        dec = -dec;
    }
    if(!dec) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    while(dec > 0) {
        out[i++] = '0' + (dec % 10);
        dec /= 10;
    }
    if(neg) out[i++] = '-';
    for(int n = 0; n < i / 2; n++) {
        char t = out[n];
        out[n] = out[i-1-n];
        out[i-1-n] = t;
    }
    out[i] = '\0';
}

void puts(const char* str) {
    if(!str)
        return;
    while(*str) {
        putchar(*str);
        str++;
    }
    putchar('\n');
}

void putstr(const char* str) {
    if(!str)
        return;
    while(*str) {
        putchar(*str);
        str++;
    }
}
extern int serialReady;

void printf(const char* fmt, ...) {
    
    va_list ap;
    va_start(ap, fmt);
    if(!fmt)
        return;
    while(*fmt) {
        if(*fmt == '%') {
            fmt++;
            switch(*fmt) {
                case 'x': {
                    int x = va_arg(ap, int);
                    char hex[9];
                    putHex(x, 0, hex);
                    putstr(hex);
                    if(serialReady)
                        serialPutStr(hex);
                    fmt++;
                    continue;
                }
                case 's': {
                    char* s = va_arg(ap, char*);
                    if(!s) {
                        putstr("(null)");
                        fmt++;
                        continue;
                    }
                    putstr(s);
                    if(serialReady)
                        serialPutStr(s);
                    fmt++;
                    continue;
                }
                case 'd': {
                    int x = va_arg(ap, int);
                    char dec[11];
                    putDec(x, dec);
                    putstr(dec);
                    if(serialReady)
                        serialPutStr(dec);
                    fmt++;
                    continue;
                }
                default: {
                    putchar(*fmt);
                    if(serialReady)
                        serialPutChar(*fmt);
                    fmt++;
                    continue;
                }
            }
        }
        putchar(*fmt);
        if(serialReady)
            serialPutChar(*fmt);
        fmt++;
    }
    va_end(ap);
}

void setColor(uint8_t color) {
    currentColor = color;
}