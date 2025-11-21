#pragma once
#include <stdint.h>
#include <io.h>

void setIrqMask(uint8_t line);
void picSendEoi(uint8_t irq);