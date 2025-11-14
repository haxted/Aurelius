#pragma once
#include <stdint.h>


typedef struct {
    uint16_t limitLo;
    uint16_t baseLo;
    uint8_t baseMi;
    uint8_t access;
    uint8_t granularity;
    uint8_t baseHi;
} __attribute__((packed)) GDTEntry;

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) GDTPtr;

void gdtInit();
