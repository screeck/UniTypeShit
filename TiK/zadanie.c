#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>


uint8_t polynomial_mod(uint32_t dividend, uint8_t divisor) {
    // Maski do sprawdzania najstarszych bit�w
    uint32_t mask_dividend = 1 << 31; 
    uint8_t mask_divisor = 1 << 7;   

    if (!(divisor & mask_divisor)) {
        printf("Divisor must have the most significant bit set!\n");
        return 0;
    }

    for (int i = 0; i < 32; i++) {
        if (dividend & mask_dividend) {
            dividend ^= ((uint32_t)divisor << (31 - 7 - i));
        }

        mask_dividend >>= 1;
    }

    return (uint8_t)dividend;
}


void print_binary(uint32_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    uint32_t dividend = 0b11001010111100001111000011110000; 
    uint8_t divisor = 0b10111011;                         


    uint8_t remainder = polynomial_mod(dividend, divisor);

    // Wy�wietlenie wynik�w
    printf("Dividend:    ");
    print_binary(dividend, 32);
    printf("\n");

    printf("Divisor:     ");
    print_binary(divisor, 8);
    printf("\n");

    printf("Remainder:   ");
    print_binary(remainder, 8);
    printf("\n");

    return 0;
}
