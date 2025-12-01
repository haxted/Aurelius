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

typedef struct {
    uint16_t link, reserved1;
    uint32_t esp0;
    uint16_t ss0, reserved2;
    uint32_t esp1;
    uint16_t ss1, reserved3;
    uint32_t esp2;
    uint16_t ss2, reserved4;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint16_t es, reserved5;
    uint16_t cs, reserved6;
    uint16_t ss, reserved7;
    uint16_t ds, reserved8;
    uint16_t fs, reserved9;
    uint16_t gs, reserved10;
    uint16_t ldtr, reserved11;
    uint16_t reserved12, iopb;
    uint32_t ssp;
} __attribute__((packed)) TSSEntry;


void gdtInit();
