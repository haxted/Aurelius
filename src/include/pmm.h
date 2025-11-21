#pragma once
#include <stdint.h>
#include <multiboot.h>

void initPmm(multiboot_info_t* mbinfo);
void* pmmAllocPage();
void pmmFreePage(void* ptr);