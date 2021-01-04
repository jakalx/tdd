#include "schwein.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

class schwein_test : public ::testing::Test {
protected:
  tiere::schwein s;
};

TEST_F(schwein_test, ctor__initializes_object_to_defaults) {
  EXPECT_THAT(s.get_gewicht(), testing::Eq (10));
  EXPECT_THAT(s.get_name(), testing::StrEq("nobody"));
}

TEST_F(schwein_test, ctor__Elsa_throws_invalid_argument_exception) {
  EXPECT_THROW(tiere::schwein{"Elsa"}, std::invalid_argument);
}

TEST_F(schwein_test, set_name__invalid_pigname_Elsa_throws_invalid_argument_exception) {
  EXPECT_THROW(s.set_name ("Elsa"), std::invalid_argument);
}

TEST_F(schwein_test, set_name__regular_name_does_not_throw) {
  s.set_name("Babe");
  EXPECT_THAT (s.get_name(), testing::Eq("Babe"));
}

TEST_F(schwein_test, fressen__increments_gewicht) {
  const auto old_weight = s.get_gewicht();
  s.fressen();
  EXPECT_THAT(s.get_gewicht(), testing::Gt(old_weight));
}
