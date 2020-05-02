#pragma once
#include <string>

struct Variable
{
	std::string name;
	double value;
	bool readonly = false;

	Variable(std::string _name, double _value, bool _readonly = false) : name(_name), value(_value), readonly(_readonly) {}
};