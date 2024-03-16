fun fizzbuzz(n: Int) {
    for (i in 1..n) {
        val outputs = arrayOf(
            i.toString(),
            "Fizz",
            "Buzz",
            "FizzBuzz"
        )
        val idx1 = if (i % 3 == 0) 1 else 0
        val idx2 = if (i % 5 == 0) 1 else 0
        val idx = (idx1 shl 1) + idx2
        println(outputs[idx])
    }
}

fizzbuzz(32)