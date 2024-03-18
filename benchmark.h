#include <stdint.h>
typedef char* (fizzbuzz_function_t)(uint32_t, char*);

void benchmark_fizzbuzz(fizzbuzz_function_t);