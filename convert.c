#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "convert.h"

// ---------------------------------------------------------------------
// Division Algorithm Conversion
// ---------------------------------------------------------------------
void div_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    while (n > 0) {
        int remainder = n % base;
        n = n / base;

        if (remainder < 10)
            temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A' + (remainder - 10);
    }

    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - i - 1];
    }
    out[pos] = '\0';
}

// ---------------------------------------------------------------------
// Subtraction Algorithm Conversion
// ---------------------------------------------------------------------
void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    uint32_t power = 1;
    while (power <= n / base) {
        power *= base;
    }

    while (power > 0) {
        int digit = n / power;
        n = n % power;
        power /= base;

        if (digit < 10)
            temp[pos++] = '0' + digit;
        else
            temp[pos++] = 'A' + (digit - 10);
    }

    temp[pos] = '\0';
    strcpy(out, temp);
}

// ---------------------------------------------------------------------
// Bit Manipulation Demonstration (Single-line format)
// ---------------------------------------------------------------------
void print_tables(uint32_t n) {
    char bin[65], oct[32], hex[32];
    char bin2[65], oct2[32], hex2[32];
    char bin3[65], oct3[32], hex3[32];

    // Original
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);

    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin2);
    div_convert(shifted, 8, oct2);
    div_convert(shifted, 16, hex2);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin3);
    div_convert(masked, 8, oct3);
    div_convert(masked, 16, hex3);

    // Print all results in one line
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s "
           "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s "
           "AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, n, hex,
           bin2, oct2, shifted, hex2,
           bin3, oct3, masked, hex3);
}
