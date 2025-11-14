#pragma once
#include <stdint.h>

#define COM1 0x3F8

void initSerial(void);
void serialPutChar(char c);
void serialPutStr(const char* str);