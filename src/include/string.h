#pragma once
#include <stdint.h>
#include <stddef.h>

void* memmove(void* dest, const void* src, int n);
void* memset(void* dest, int c, int n);
int memcmp(const void* n1, const void* n2, size_t len);
void* memcpy(void* dest, const void* src, size_t n);
size_t strlen(const char* str);