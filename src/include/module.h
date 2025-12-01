#pragma once
#include <stdint.h>
#include <multiboot.h>

void* getModuleByFileName(const char* fileName, multiboot_info_t* mbinfo, uintptr_t* end);
