#include "Fibonacci.hpp"
#include <iostream>

int main() {
    for(auto i=1; i<20; i++) {
        std::cout << i << ": " << Fibonacci::fibonacci(i) << std::endl;
    }

    return 0;
}
