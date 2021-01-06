#include "myservice_using_dependency_test.h"

// member
std::string dependency_to_fake::get_firstname() const
{
  return dependency_to_fake_mock_repo::getInstance().getMock().get_firstname();
}

// static
string dependency_to_fake::get_lastname()
{
  return dependency_to_fake_mock_repo::getInstance().getMock().get_lastname();
}

// virtual
long dependency_to_fake::calculate(const int value) const
{
  return dependency_to_fake_mock_repo::getInstance().getMock().calculate(value);
}

TEST_F(myservice_using_dependency_test, FirstMethod)
{
  EXPECT_CALL(dMock, get_firstname()).WillOnce(::testing::Return("Peter"));
  EXPECT_EQ(object_under_test.first_method_under_test(), "Peter Hallo");
}

TEST_F(myservice_using_dependency_test, SecondMethod) {
	EXPECT_CALL(dMock, get_lastname()).WillOnce(::testing::Return("Peter"));
	EXPECT_EQ(object_under_test.second_method_under_test(), "Peter Hallo");
}

TEST_F(myservice_using_dependency_test, ThirdMethod)
{
  EXPECT_CALL(dMock, calculate(::testing::_)).WillOnce(::testing::Return(42));
  EXPECT_EQ(object_under_test.third_method_under_test(2), 42);
}
