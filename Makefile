all: hyperfizz naive_fizzbuzz

hyperfizz: hyperfizz.c benchmark.h benchmark.c  Makefile
	clang -O3 -Wall -Werror hyperfizz.c benchmark.c -ohyperfizz

naive_fizzbuzz: naive_fizzbuzz.c benchmark.h benchmark.c Makefile
	clang -O3 -Wall -Werror naive_fizzbuzz.c benchmark.c -onaive_fizzbuzz


.PHNOY: benchmark
benchmark: naive_fizzbuzz hyperfizz fb_stringbuilder.kts
	./hyperfizz
	./naive_fizzbuzz
	kotlin -J-Xmx10G fb_stringbuilder.kts