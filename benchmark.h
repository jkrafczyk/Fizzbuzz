#include <stdint.h>
typedef char* (fizzbuzz_function_t)(uint32_t, char*);

void benchmark_fizzbuzz(char *function_name, fizzbuzz_function_t);