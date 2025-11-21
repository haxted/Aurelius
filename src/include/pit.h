#pragma once
#include <stdint.h>

enum {
    CHANNEL0_DAT = 0x40,
    CHANNEL1_DAT,
    CHANNEL2_DAT,
    MODE_CMD_REG,
};

void pitStartCounter(uint16_t count);
void initPit();