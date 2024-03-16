enum class OutputType(
    val condition: (Int) -> Boolean,
    val printer: (Int) -> Unit
) {
    FIZZBUZZ(
        { it % 15 == 0},
        { println("fizzbuzz")}
    ),
    BUZZ(
        { it % 5 == 0 },
        { println("buzz")}
    ),
    FIZZ(
        {it % 3 == 0 },
        { println("fizz")}
    ),
    FALLBACK(
        { true },
        { println(it) }
    )
}

fun fizzbuzz(maxN: Int) {
    for (n in 1..maxN) {
        for (v in OutputType.values()) {
            if (v.condition(n)) {
                v.printer(n)
                break
            }
        }
    }
}

fizzbuzz(32)