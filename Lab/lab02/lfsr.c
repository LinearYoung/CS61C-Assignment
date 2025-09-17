#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    uint16_t bit0 = *reg & 1;
    uint16_t bit2 = (*reg >> 2) & 1;
    uint16_t bit3 = (*reg >> 3) & 1;
    uint16_t bit5 = (*reg >> 5) & 1;

    uint16_t add_val = bit0 ^ bit2 ^ bit3 ^ bit5;
    *reg = (*reg >> 1) | (add_val << 15);
    /* YOUR CODE HERE */
}

