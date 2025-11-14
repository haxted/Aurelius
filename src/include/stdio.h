#pragma once
#include <stdint.h>
#include <stdarg.h>

#define VGA_WID 80
#define VGA_HEI 25

void putchar(char c);
void puts(const char* str);
void setColor(uint8_t color);
void printf(const char* fmt, ...);