#ifndef CALCULATOR_IMPL_H
#define CALCULATOR_IMPL_H

#include "calculator.hpp"

namespace calculator {
  class CalculatorImpl : public Calculator {
    long mult_impl(int a, int b) override {
      int res{0};
      for (int i = 0; i < a; ++i) {
        res += b;
      }
      return res;
    }
  };
}

#endif /* CALCULATOR_IMPL_H */
