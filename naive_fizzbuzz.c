#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"

char *fizzbuzz(unsigned max_n, char *buffer) {
    char *full_output = buffer;
    char *output_so_far = full_output;
    static char *number = NULL;
    if (number == NULL) {
        number = malloc(11);
    }

    for (unsigned n=1; n <= max_n; n++) {
        if (n%15 == 0) {
            output_so_far += sprintf(output_so_far, "fizzbuzz");
        } else if (n % 5 == 0) {
            output_so_far += sprintf(output_so_far, "buzz");
        } else if (n % 3 == 0) {
            output_so_far += sprintf(output_so_far, "fizz");
        } else {
            output_so_far += sprintf(output_so_far, "%d", n);
        }
        *output_so_far++ = '\n';
    }
    *output_so_far = 0;
    return full_output;
}

int main(int argc, char **argv) {
    benchmark_fizzbuzz("naive_fizzbuzz", fizzbuzz);
    return 0;
}