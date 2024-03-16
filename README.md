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
Tested on a MacBook Air M2:
```
Running benchmark for hyperfizz.
  Took 14516 ms for 25 repetitions with n=100000000.
  580 ms per repetition
Running benchmark for naive_fizzbuzz.
  Took 50946 ms for 25 repetitions with n=100000000.
  2037 ms per repetition
Running benchmark for fb_stringbuilder.
  Took 42831 ms for 25 repetitions with n=100000000
  1713 ms per repetition
```