#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <time.h>
#include <stdint.h>
#include "benchmark.h"

char *fizzbuzz(uint32_t max_n, char *buffer) {
    char *full_output = buffer;
    char *output_so_far = full_output;
    static char *number = NULL;
    if (number == NULL) {
        number = malloc(16);
    }
    static uint32x4_t DIVISORS_SMALL = {10, 100, 1000, 10000};
    static uint32x4_t DIVISORS_LARGE = {100000, 1000000, 10000000, 100000000};

    for (uint32_t n=1; n <= max_n; n++) {
        uint8_t n_digits = 1;

        uint32x4_t n_vec = vdupq_n_u32(n); // n_vec = {n, n, n, n}
        // Test if larger than <elements of DIVISORS_SMALL>
        uint32x4_t count = vcgeq_u32(n_vec, DIVISORS_SMALL); // n >= DIVISORS_SMALL[0..3]
        count = vnegq_s32(count); // count[0..3] = -count[0..3]
        n_digits += vaddvq_s32(count); // n_digits += sum(count[0..3])

        // Same, for <DIVISORS_LARGE>
        count = vcgeq_u32(n_vec, DIVISORS_LARGE);
        count = vnegq_s32(count);
        n_digits += vaddvq_s32(count);

        // Do we need the last, biggest, digit?
        n_digits += n >= 1000000000;

        // Difficult to vectorize: neon doesn't seem to have integer divivision/modulo operations :(
        unsigned n2 = n;
        number[n_digits-1] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-2] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-3] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-4] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-5] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-6] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-7] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-8] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-9] = '0' + (n2 % 10);
        n2 /= 10;
        number[n_digits-10] = '0' + (n2 % 10);
        number[n_digits] = 0;
    
        char *possible_outputs[] = {
            number,
            "fizz            ",
            "buzz            ",
            "fizzbuzz        "
        };
        int lengths[] = {
            n_digits, 
            4,
            4,
            8
        };
        int is_fizzy = (n % 3) == 0;
        int is_buzzy = (n % 5) == 0;
        int output_index = (is_fizzy & 0x1) + ((is_buzzy & 0x1) << 1);

        *(__uint128_t*)output_so_far = *(__uint128_t*)(possible_outputs[output_index]);
        output_so_far += lengths[output_index];
        output_so_far[0] = '\n';
        output_so_far++;
    }
    *output_so_far = 0;
    return full_output;
}

int main(int argc, char **argv) {
    benchmark_fizzbuzz("hyperfizz", fizzbuzz);
    return 0;
}