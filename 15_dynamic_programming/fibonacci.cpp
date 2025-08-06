#include <iostream>
#include "../common/timer.h"

// Standard recursive approach (inefficient)
int fib_standard(int n) {
    if (n <= 1) return n;
    return fib_standard(n - 1) + fib_standard(n - 2);
}

// Optimized iterative approach
int fib_iterative(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1, current = 0;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main() {
    int n = 30;

    std::cout << "Computing Fibonacci(" << n << ")...\n";

    {
        Timer<std::micro> timer("Iterative Fibonacci");
        int result = fib_iterative(n);
        std::cout << "Result (iterative): " << result << std::endl;
    }

    {
        Timer<std::micro> timer("Recursive Fibonacci");
        int result = fib_standard(n);
        std::cout << "Result (recursive): " << result << std::endl;
    }

    return 0;
}
