// Example: Google Test with Fibonacci
#include <gtest/gtest.h>
#include "../common/timer.h"

// Simple recursive fibonacci
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// Dynamic programming fibonacci
int fib_dp(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1, current = 0;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

// Test cases
TEST(FibonacciTest, BaseCase) {
    EXPECT_EQ(fib_dp(0), 0);
    EXPECT_EQ(fib_dp(1), 1);
    EXPECT_EQ(fib_recursive(0), 0);
    EXPECT_EQ(fib_recursive(1), 1);
}

TEST(FibonacciTest, SmallNumbers) {
    EXPECT_EQ(fib_dp(5), 5);
    EXPECT_EQ(fib_dp(10), 55);
    EXPECT_EQ(fib_recursive(5), 5);
    EXPECT_EQ(fib_recursive(10), 55);
}

TEST(FibonacciTest, Performance) {
    Timer<std::micro> timer("DP Fibonacci(30)");
    int result_dp = fib_dp(30);
    // Timer destructor will print timing

    EXPECT_EQ(result_dp, 832040);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
