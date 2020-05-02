#pragma once
#include <vector>
#include "Variable.h"

double eval(std::string input, std::vector<Variable> variables = {});
int NumberIndexRequest(std::string& str, int& index, bool backwards = false);
int coefficient(std::string& input, int index);
double tolerance(double d);
