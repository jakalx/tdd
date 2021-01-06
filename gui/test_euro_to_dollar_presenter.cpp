#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "euro_to_dollar_presenter_impl.h"
#include "euro_to_dollar_view.h"
#include "euro_to_dollar_calculator.h"

using namespace testing;

class Mock_euro_to_dollar_view : public euro_to_dollar_view {
public:
  MOCK_METHOD(void, set_presenter, (euro_to_dollar_presenter *), (override));
  MOCK_METHOD(void, dispose, (), (override));
  MOCK_METHOD(std::string, get_euro, (), (const, override));
  MOCK_METHOD(void, set_euro, (std::string), (override));
  MOCK_METHOD(std::string, get_dollar, (), (const, override));
  MOCK_METHOD(void, set_dollar, (std::string), (override));
  MOCK_METHOD(bool, is_rechnen_enabled, (), (const, override));
  MOCK_METHOD(void, set_rechnen_enabled, (bool), (override));
};

class Mock_euro_to_dollar_model : public euro_to_dollar_calculator {
public:
  MOCK_METHOD(double, convert, (const double), (const, override));
};

class Test_euro_to_dollar_presenter : public Test {
protected:
  void SetUp() override {
    testee.set_model(&model);
    testee.set_view(&view);
  }
  NiceMock<Mock_euro_to_dollar_view> view;
  Mock_euro_to_dollar_model model;
  euro_to_dollar_presenter_impl testee;
};

TEST_F(Test_euro_to_dollar_presenter, populate_items__initilizes_view_with_default_values) {
  EXPECT_CALL(view, set_euro("0.0"));
  EXPECT_CALL(view, set_dollar("0.0"));
  EXPECT_CALL(view, set_rechnen_enabled(true));
  testee.populate_items();
}

TEST_F(Test_euro_to_dollar_presenter, rechnen__fills_dollar_field_with_error_on_invalid_input)
{
  EXPECT_CALL(view, get_euro()).WillRepeatedly(Return("nan"));
  EXPECT_CALL(view, set_dollar("invalid input"));
  testee.rechnen();
}

TEST_F(Test_euro_to_dollar_presenter, rechnen__fills_dollar_field_with_error_on_conversion_error)
{
  EXPECT_CALL(view, get_euro()).WillRepeatedly(Return("42"));
  EXPECT_CALL(model, convert(_)).WillRepeatedly(Throw(std::runtime_error("some error")));
  EXPECT_CALL(view, set_dollar("some error"));
  testee.rechnen();
}

TEST_F(Test_euro_to_dollar_presenter, rechnen__forwards_valid_input_to_model)
{
  EXPECT_CALL(view, get_euro()).WillRepeatedly(Return("23.50"));
  EXPECT_CALL(model, convert(23.5));
  testee.rechnen();
}

TEST_F(Test_euro_to_dollar_presenter, rechnen__fills_dollar_field_with_result_from_conversion)
{
  EXPECT_CALL(view, get_euro()).WillRepeatedly(Return("23.50"));
  EXPECT_CALL(model, convert(23.5)).WillRepeatedly(Return(42.0));
  EXPECT_CALL(view, set_dollar("42.00"));
  testee.rechnen();
}

TEST_F(Test_euro_to_dollar_presenter, beenden__calls_dispose_on_view)
{
  EXPECT_CALL(view, dispose);
  testee.beenden();
}
