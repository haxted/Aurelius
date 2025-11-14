#pragma once
#include <stdint.h>
uint8_t inb(uint16_t port);
void outb(uint8_t dat, uint16_t port);