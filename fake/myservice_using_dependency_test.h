#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <deque>
#include <map>
#include "my_service_using_dependency.h"

class dependency_to_fake_mock
{
public:
    MOCK_METHOD(std::string, get_firstname,());
    MOCK_METHOD(std::string, get_lastname, ());
    MOCK_METHOD(long, calculate, (const int));
};

class dependency_to_fake_mock_repo
{
public:
    ~dependency_to_fake_mock_repo() = default;
    void set_mock_to_use(dependency_to_fake_mock &dependency_to_fake_mock_) {
      mock_ = &dependency_to_fake_mock_;
    }

    dependency_to_fake_mock& getMock()
    {
      assert (mock_);
      return *mock_;
    }

    static dependency_to_fake_mock_repo& getInstance() {
        static dependency_to_fake_mock_repo instance;
        return instance;
    }

private:
    dependency_to_fake_mock *mock_;
    dependency_to_fake_mock_repo() = default;
};


class myservice_using_dependency_test:public ::testing::Test
{
protected:
  void SetUp() override {
    dependency_to_fake_mock_repo::getInstance().set_mock_to_use(dMock);
  }
  my_service_using_dependency object_under_test;
  dependency_to_fake_mock dMock;
};
