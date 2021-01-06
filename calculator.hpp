#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calculator {
  class Calculator {
  public:
    virtual ~Calculator() = default;

    long mult (int a, int b) {
      return mult_impl(a, b);
    }

  private:
    [[nodiscard]] virtual long mult_impl (int a, int b) = 0;
  };
}

#endif /* CALCULATOR_H */
