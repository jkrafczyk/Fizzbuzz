all: hyperfizz naive_fizzbuzz hyperfizz_novector

hyperfizz: hyperfizz.c benchmark.h benchmark.c  Makefile
	clang -DVARIANT_NAME="hyperfizz" -march=native -O3 -Wall -Werror hyperfizz.c benchmark.c -ohyperfizz

hyperfizz_novector: hyperfizz.c benchmark.h benchmark.c  Makefile
	clang -DNO_VECTORS -DVARIANT_NAME="hyperfizz_novector" -march=native -O3 -Wall -Werror hyperfizz.c benchmark.c -ohyperfizz_novector

naive_fizzbuzz: naive_fizzbuzz.c benchmark.h benchmark.c Makefile
	clang -DVARIANT_NAME="naive_fizzbuzz" -O3 -Wall -Werror naive_fizzbuzz.c benchmark.c -onaive_fizzbuzz


.PHNOY: benchmark
benchmark: naive_fizzbuzz hyperfizz_novector hyperfizz fb_stringbuilder.kts
	./hyperfizz
	./hyperfizz_novector
	./naive_fizzbuzz
	kotlin -J-Xmx10G fb_stringbuilder.kts
