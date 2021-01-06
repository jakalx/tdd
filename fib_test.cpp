#include <gtest/gtest.h>
#include "Fibonacci.hpp"

TEST(test_my_class, test_10th_fibonacci_nr_is_55)
{
    EXPECT_EQ(Fibonacci::fibonacci(10), 55);
}
