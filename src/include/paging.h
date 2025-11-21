#pragma once
#include <stdio.h>
#include <stdint.h>
#include <panic.h>
#include <pmm.h>

enum {
    PDE_PRESENT = 1 << 0,
    PDE_RW      = 1 << 1,
    PDE_US      = 1 << 2,
    PDE_PWT     = 1 << 3,
    PDE_PCD     = 1 << 4,
    PDE_A       = 1 << 5,
    PDE_IGN     = 1 << 6,
    PDE_PS      = 1 << 7,
    PDE_PHYS    = 0xFFFFF000
};

enum {
    PTE_PRESENT = 1 << 0,
    PTE_RW      = 1 << 1,
    PTE_US      = 1 << 2,
    PTE_PWT     = 1 << 3,
    PTE_PCD     = 1 << 4,
    PTE_A       = 1 << 5,
    PTE_D       = 1 << 6,
    PTE_PAT     = 1 << 7,
    PTE_G       = 1 << 8,
    PTE_PHYS    = 0xFFFFF000
};

#define GET_OFF(addr) ((uint32_t)(addr) & 0xFFF)
#define GET_PD(addr)  (((uint32_t)(addr) & 0xFFC00000) >> 22)
#define GET_PT(addr)  (((uint32_t)(addr) & 0x3FF000) >> 22)

void loadPageDir(void* pageDir);
void mapAddr(void* phys, void* virt, int flags);
void initPaging(uint32_t identMapLen);