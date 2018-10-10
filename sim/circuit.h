#pragma once
#include "icemu.h"

typedef struct {
    ICeChip mcu;
    ICeChip cnt1;
    ICeChip cnt2;
} FreqCounter;

void freqcounter_circuit_init(
    FreqCounter *circuit, ICePin *outser, ICePin *outclk, ICePin *input);

