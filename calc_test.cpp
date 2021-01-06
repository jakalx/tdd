#include "gmock/gmock-function-mocker.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "calculator.hpp"
#include "calculator_optimizer.hpp"

class CalculatorMock : public calculator::Calculator {
public:
  MOCK_METHOD(long, mult_impl, (int a, int b), (override));
};

namespace calculatorTest {
  using namespace calculator;
  using namespace testing;
  class CalculatorOptimizerTest : public ::testing::Test {
  protected:
    void SetUp() override {
      EXPECT_CALL(calculatorMock, mult_impl(3, 4))
          .WillRepeatedly(Return(3 * 4));
    }

    CalculatorMock calculatorMock;
    CalculatorOptimizer testee{calculatorMock};
  };

  TEST_F(CalculatorOptimizerTest, mult__a_less_than_b_dont_get_swapped) {
    testee.mult(3, 4);
  }

  TEST_F(CalculatorOptimizerTest, mult__a_greater_than_b_get_swapped) {
    testee.mult(4,3);
  }
}
