#ifndef CALCULATOR_OPTIMIZER_H
#define CALCULATOR_OPTIMIZER_H

#include "calculator.hpp"

namespace calculator {
  class CalculatorOptimizer : public Calculator {
    Calculator& calc_;

    long mult_impl(int a, int b) override {
      if (a <= b) {
        return calc_.mult(a, b);
      } else {
        return calc_.mult(b, a);
      }
    }

  public:
    CalculatorOptimizer(Calculator& calc) : calc_(calc) {}
  };
}

#endif /* CALCULATOR_OPTIMIZER_H */
