#pragma once
#include <stdint.h>
#include <stdio.h>


typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) IDTPtr;

typedef struct {
    uint16_t offsetLo;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offsetHi;
} __attribute__((packed)) IDTGate;

void idtSetGate(uint8_t gate, uint32_t offset, uint16_t selector, uint8_t flags);
void idtInit();