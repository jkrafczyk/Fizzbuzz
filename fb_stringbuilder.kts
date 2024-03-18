import kotlin.text.StringBuilder
import kotlin.system.measureTimeMillis

fun fizzbuzz(n: Int): String {
    val output = StringBuilder(11*n)
    for (i in 1..n) {
        if (i % 15 == 0) {
            output.append("fizzbuzz\n")
        } else if (i % 5 == 0) {
            output.append("buzz\n")
        } else if (i % 3 == 0) {
            output.append("fizz\n")
        } else {
            output.append(i.toString() + "\n")
        }
    }
    return output.toString()
}

fun benchmark(n: Int, repetitions: Int) {
    println("Warming up.")
    fizzbuzz(n)
    fizzbuzz(n)
    fizzbuzz(n)
    fizzbuzz(n)

    System.err.println("Running benchmark for fb_stringbuilder.")
    val millis = measureTimeMillis {
        for (i in 1..repetitions) {
            fizzbuzz(n)
            fizzbuzz(n)
            fizzbuzz(n)
            fizzbuzz(n)
            fizzbuzz(n)
        }
    }
    val totalRepetitions = 5*repetitions
    System.err.println("  Took $millis ms for $totalRepetitions repetitions with n=$n")
    System.err.println("  ${millis/totalRepetitions} ms per repetition")
}

// For comparison: hyperfizz takes ~570ms per iteration at n=100_000_000
// naive_fizzbuzz takes just over 2 seconds at the same setting.
// This took 1300ms. Needed to be run with kotlin -J-Xmx10G fb_stringbuilder.kts
benchmark(100_000_000, 5)