#pragma once


#include <QtTest>
#include <QCoreApplication>
#include <QPushButton>
#include <QLineEdit>

#include "EuroToDollarCalculatorApplication.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mockeuro_to_dollar_presenter.h"
#include <string_view>
#include <fmt/core.h>

using namespace ::testing;

template<typename T, typename W>
T *require_child(W &widget, std::string_view name)
{
  if (auto res = widget.template findChild<T *>(name.data()); res) {
    return res;
  } else {
    throw std::logic_error(fmt::format("no such gui element: {} of type {}", name, typeid(T).name()));
  }
}

class EuroToDollarCalculatorApplicationTest : public Test
{
protected:
    int i = 0;
    QApplication app{ i, nullptr };
    NiceMock<Mockeuro_to_dollar_presenter> p;
    EuroToDollarCalculatorApplication objectUnderTest;
	void SetUp() override
	{
        objectUnderTest.set_presenter(&p);
	}

  QPushButton* get_btn_rechnen() {
    return require_child<QPushButton>(objectUnderTest, "btn_rechnen");
  }
  QPushButton *get_btn_beenden()
  {
    return require_child<QPushButton>(objectUnderTest, "btn_beenden");
  }
  QLineEdit *get_txt_euro()
  {
    return require_child<QLineEdit>(objectUnderTest, "txt_euro");
  }
};
