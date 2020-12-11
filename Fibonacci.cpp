#include "Fibonacci.hpp"

unsigned int Fibonacci::fibonacci(unsigned int num) {
    if (num == 0) {
        return 0;
    }

    if (num == 1) {
        return 1;
    }
    return fibonacci(num - 1) + fibonacci(num - 2);
}