# Fast-Fizzbuzz

This repository contains several FizzBuzz implementations in C and Kotlin. The initial goal was mainly to just go with architecturally unusual approaches, but a few solutions were specifically designed for performance comparisons.

## Descriptions of the various solutions

* [fb_enum.kts](fb_enum.kts)
  This defines the different types of outputs, combined with a condition on when they apply, as elements of an enum. For each printed number uses the first enum value with a matching condition to generate the output for that number.
* [fb_array.kts](fb_array.kts) 
  For each number, all four possible outputs (fizz, buzz, fizzbuzz, the number itself) are generated and stored in an array. Based on the division remainders of the number by 3 and 5, an index into the array is calculated
  and the corresponding output printed.
* [fb_stringbuilder.kts](fb_stringbuilder.kts)
  Mostly a naive implementation, but the entire output is collected in a StringBuilder to avoid IO operations inside the loop. Output is then printed afterward in a single println statement. 
* [naive_fizzbuzz.c](naive_fizzbuzz.c)
  basically identical to the previous one, but in C.
* [hyperfizz.c](hyperfizz.c)
  Branchless, partially vectorized, high-performance Fizzbuzz. 
  This combines the approach from fb_array.kts - writing all possible outputs into an array and selecting from it - with the technique of keeping the entire output in RAM instead of writing it to the console immediately.  
  Additionally, it completely avoids function calls within the loop. The number-to-string-conversion is implemented manually. Determining the length of the number in characters for proper output into the buffer is done using NEON vector instructions.  
  The end effect is that there are no conditional branches within the loop body, avoiding the cost of branch mispredictions. The only repeatedly occurring conditional branch while generating the output is the loop condition itself, which should be correctly handled by the branch predictor the majority of the time.

## Benchmark results
Tested on a MacBook Pro with M3 Pro CPU:
```
Running benchmark for hyperfizz.
  Took 12313 ms for 25 repetitions with n=100000000.
  492 ms per repetition
Running benchmark for hyperfizz_novector.
  Took 12896 ms for 25 repetitions with n=100000000.
  515 ms per repetition
Running benchmark for naive_fizzbuzz.
  Took 44240 ms for 25 repetitions with n=100000000.
  1769 ms per repetition
Running benchmark for fb_stringbuilder.
  Took 24282 ms for 25 repetitions with n=100000000
  971 ms per repetition
```

Using NEON to calculate the length of the printed number reliably improves runtime, but only very slightly. 
| Variant | ms | in relation to naive_fizzbuzz | in relation to vectorized hyperfizz |
|--|--|--|--|
| naive_fizzbuzz | 1769 | 100% | 360% |
| fb_stringbuilder | 971 | 55% | 197% |
| hyperfizz_novector | 515 | 29% | 105% | 
| **hyperfizz** | **492** | **28%** | **100%** |


Tested on a AMD Ryzen 9 3900X:
```
Running benchmark for hyperfizz.
  Took 24792 ms for 25 repetitions with n=100000000.
  991 ms per repetition
Running benchmark for hyperfizz_novector.
  Took 24259 ms for 25 repetitions with n=100000000.
  970 ms per repetition
Running benchmark for naive_fizzbuzz.
  Took 70187 ms for 25 repetitions with n=100000000.
  2807 ms per repetition
Running benchmark for fb_stringbuilder.
  Took 37987 ms for 25 repetitions with n=100000000
  1519 ms per repetition
```

Using AVX2 to calculate the length of the printed number reliably worsens runtime. (Although that may well be due to my incompetence!)

| Variant | ms | in relation to naive_fizzbuzz | in relation to vectorized hyperfizz |
|--|--|--|--|
| naive_fizzbuzz | 2807 | 100% | 283% |
| fb_stringbuilder | 1519 | 54% | 153% |
| **hyperfizz_novector** | **970** | **34.5%** | **98%** |
| hyperfizz | 991 | 35.3% | 100% |
