// -*- mode: c++ -*-
#pragma once
#include <string>
class person
{
private:
	std::string id;
	std::string vorname;
	std::string nachname;

public:
	person():id(""),vorname("John"),nachname("Doe"){}
	void SetId(std::string id)
	{
		this->id = id;
	}
	void SetVorname(std::string vorname)
	{
		this->vorname = vorname;
	}
	void SetNachname(std::string nachname)
	{
		this->nachname = nachname;
	}

	std::string GetVorname() const
	{
		return this->vorname;
	}
	std::string GetNachname()const
	{
		return this->nachname;
	}
	std::string GetId()const
	{
		return this->id;
	}
};

inline bool operator==(const person &lhs, const person& rhs)
{
  return lhs.GetId() == rhs.GetId()
    && lhs.GetVorname() == rhs.GetVorname()
    && lhs.GetNachname() == rhs.GetNachname();
}
