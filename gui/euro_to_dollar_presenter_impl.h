#pragma once
#include "euro_to_dollar_presenter.h"
#include "euro_to_dollar_view.h"
#include <optional>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cassert>

class euro_to_dollar_presenter_impl :
    public euro_to_dollar_presenter
{
private:
	euro_to_dollar_view* view_{nullptr};
	euro_to_dollar_calculator* model_{ nullptr };

  std::optional<double> string_to_euro(const std::string& s) const try {
    std::istringstream ss(s);
    ss.imbue(std::locale("en_US.utf-8"));
    long double d{0.0};
    ss >> std::get_money(d);
    if (ss) {
      return d;
    } else {
      return {};
    }
  } catch (...) {
    return {};
  }

  std::string dollar_to_string(const double d) const
  {
    std::ostringstream ss;
    ss.imbue(std::locale("en_US.utf-8"));
    ss << std::put_money(d);
    return ss.str();
  }

public:
  euro_to_dollar_presenter_impl() = default;

  void set_model(euro_to_dollar_calculator *model) override
  {
    assert (model);
    model_ = model;
	}

	void set_view(euro_to_dollar_view* view) override
	{
    assert(view);
    view_ = view;
    populate_items();
	}

	void populate_items() const override
	{
    view_->set_euro("0.0");
    view_->set_dollar("0.0");
    view_->set_rechnen_enabled(true);
  }

	void rechnen() const override try
	{
    if (const auto euro = string_to_euro(view_->get_euro()); euro) {
      view_->set_dollar (dollar_to_string(model_->convert (*euro / 100.0) * 100.0));
    } else {
      view_->set_dollar("invalid input");
    }
	} catch (const std::exception& ex) {
    view_->set_dollar(ex.what());
  }

	void beenden() const override
	{
    view_->dispose();
	}

	void update_rechnen_action_state() const override
	{
    const auto input_is_valid = string_to_euro(view_->get_euro()).has_value();
    view_->set_rechnen_enabled(input_is_valid);
  }
};
