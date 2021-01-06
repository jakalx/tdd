#pragma once
#include <exception>

class personen_service_exception :
    public std::exception
{
public:
	personen_service_exception(char const* const message);
};

