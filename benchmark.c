#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void benchmark_fizzbuzz(char *function_name, fizzbuzz_function_t fizzer) {
    uint32_t n = 100000000;
    // Output is _at most_ 10 chars (large 32-bit int) plus newline for every iteration. max_n*11 bytes plus terminating 0 should be enough for everyone.
    char *out = malloc(11*n+1);  

    // One round to demonstrate this mostly works:
    fizzer(132, out);
    printf("%s\n", out);

    // a few runs for warm-up:
    fizzer(n, out);
    fizzer(n, out);
    fizzer(n, out);
    fizzer(n, out);

    // Actual benchmarking:
    fprintf(stderr, "Running benchmark for %s.\n", function_name);
    int num_iters = 5;
    int calls_per_iter = 5;
    clock_t start = clock(), diff;
    for (int i=0; i<num_iters; i++) { 
        fizzer(n, out);
        fizzer(n, out);
        fizzer(n, out);
        fizzer(n, out);
        fizzer(n, out);
    }
    diff = clock() - start;
    double milliseconds = diff *  1000.0 / CLOCKS_PER_SEC;
    fprintf(stderr, "  Took %i ms for %d repetitions with n=%u.\n", (int)milliseconds, calls_per_iter*num_iters, n);
    fprintf(stderr, "  %i ms per repetition\n", (int)(milliseconds / num_iters / calls_per_iter));
    free(out);
}