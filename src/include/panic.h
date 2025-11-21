#pragma once
#include <stdio.h>


typedef struct _StackFrame {
    struct _StackFrame* n;
    uintptr_t ret;
} StackFrame;


void _panic(const char* reason, int line, const char* file);

#define panic(reason) _panic(reason, __LINE__, __FILE__)
