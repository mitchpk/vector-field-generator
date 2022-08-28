// This is horrible... I am so sorry for anyone reading this. But hey, it has been two years, and I now know how to properly parse input!

#include "InputRecognition.h"
#include <algorithm>

double eval(std::string input, std::vector<Variable> variables) {
	char* d;
	double converted1 = strtod(input.c_str(), &d);
	if (*d) {
		input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

		while (input.find(")(") != std::string::npos) {
			int temp = input.find(")(");
			input.insert(temp + 1, 1, '*');
		}

		for (int i = 1; i < input.length(); i++)
		{
			if (input[i] == '(') {
				i -= coefficient(input, i);
			}
		}

		for (int i = 0; i < variables.size(); i++)
		{
			std::string varTemp = variables[i].name;
			while (input.find(varTemp) != std::string::npos) {
				int temp = input.find(varTemp);
				if (temp != 0) {
					int minNumIndex = NumberIndexRequest(input, temp, true);
					if (minNumIndex < temp) { input.replace(temp, varTemp.length(), "*" + std::to_string(variables[i].value)); }
					else if (true) {
						for (int j = 0; j < variables.size(); j++)
						{
							if (temp >= variables[j].name.length() && input.substr(temp - variables[j].name.length(), variables[j].name.length()) == variables[j].name) {
								input.replace(temp, varTemp.length(), "*" + std::to_string(variables[i].value));
							}
							else if (j == variables.size() - 1) { input.replace(temp, varTemp.length(), std::to_string(variables[i].value)); }
						}
					}
				}
				else { input.replace(temp, varTemp.length(), std::to_string(variables[i].value)); }
			}
		}

		while (input.find("arcsin") != std::string::npos) {
			int temp = input.find("arcsin");
			temp += (coefficient(input, temp) + 5);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));
			input.replace(temp - 5, maxNumIndex - temp + 1, std::to_string(asin(a)));
		}

		while (input.find("sin") != std::string::npos) {
			int temp = input.find("sin");
			temp += (coefficient(input, temp) + 2);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));
			input.replace(temp - 2, maxNumIndex - temp + 1, std::to_string(sin(a)));
		}

		while (input.find("cos") != std::string::npos) {
			int temp = input.find("cos");
			temp += (coefficient(input, temp) + 2);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));
			input.replace(temp - 2, maxNumIndex - temp + 1, std::to_string(cos(a)));
		}

		while (input.find("ln") != std::string::npos) {
			int temp = input.find("ln");
			temp += (coefficient(input, temp) + 1);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));
			input.replace(temp - 1, maxNumIndex - temp + 1, std::to_string(log(a)));
		}

		while (input.find("^") != std::string::npos) {
			int temp = input.find("^");
			int minNumIndex = NumberIndexRequest(input, temp, true);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(minNumIndex, temp - minNumIndex));
			double b = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));

			input.replace(minNumIndex, maxNumIndex - minNumIndex + 1, std::to_string(pow(a, b)));
		}

		while (input.find("/") != std::string::npos) {
			int temp = input.find("/");
			int minNumIndex = NumberIndexRequest(input, temp, true);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(minNumIndex, temp - minNumIndex));
			double b = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));

			input.replace(minNumIndex, maxNumIndex - minNumIndex + 1, std::to_string(a / b));
		}

		while (input.find("*") != std::string::npos) {
			int temp = input.find("*");
			int minNumIndex = NumberIndexRequest(input, temp, true);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(minNumIndex, temp - minNumIndex));
			double b = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));

			input.replace(minNumIndex, maxNumIndex - minNumIndex + 1, std::to_string(a * b));
		}

		//Subtraction
		while (input.find("--") != std::string::npos) {
			input.replace(input.find("--"), 2, "+");
		}

		for (int i = 1; i < input.length(); i++)
		{
			if (input[i] == '-') {
				int minNumIndex = NumberIndexRequest(input, i, true);
				int maxNumIndex = NumberIndexRequest(input, i);
				if (minNumIndex != i && maxNumIndex != i) {
					input.insert(i, 1, '+');
					i++;
				}
			}
		}

		while (input.find("+") != std::string::npos) {
			int temp = input.find("+");
			int minNumIndex = NumberIndexRequest(input, temp, true);
			int maxNumIndex = NumberIndexRequest(input, temp);
			double a = std::stod(input.substr(minNumIndex, temp - minNumIndex));
			double b = std::stod(input.substr(temp + 1, maxNumIndex - temp + 1));

			input.replace(minNumIndex, maxNumIndex - minNumIndex + 1, std::to_string(a + b));
		}

		input.erase(std::remove(input.begin(), input.end(), '('));
		input.erase(std::remove(input.begin(), input.end(), ')'));

		char* p;
		double converted2 = strtod(input.c_str(), &p);
		if (*p) { return 0; }
		else { return (std::stod(input)); }
	}
	else { return (std::stod(input)); }
}

int NumberIndexRequest(std::string& str, int& index, bool backwards)
{
	int iDirection = backwards ? -1 : 1;
	int counter = index - 1;

	if (std::isdigit(str[iDirection + index]) || ((str[iDirection + index] == '.' || str[iDirection + index] == '-') && std::isdigit(str[iDirection + index + 1]))) {
		for (int i = index + iDirection; (i >= 0 || i < str.length()); i += iDirection)
		{
			if (std::isdigit(str[i]) || ((str[i] == '.' || str[i] == '-') && std::isdigit(str[i + 1]))) { counter += iDirection; }
			else { break; }
		}
		if (iDirection == 1) { counter += 2; }
		return (counter - iDirection);
	}
	else if (str[index + iDirection] == '(' && iDirection == 1 || str[index + iDirection] == ')' && iDirection == -1) {
		int j = 0;
		for (int i = index + iDirection; (i >= 0 || i < str.length()); i += iDirection)
		{
			if (str[i] == '(') { j++; }
			if (str[i] == ')') { j--; }
			if (j == 0)
			{
				if (i > index + iDirection)
				{
					double temp = eval(str.substr(index + 2, i - index - 2));
					str.replace(index + iDirection, i - index, std::to_string(temp));
					return(index + (std::to_string(temp).length()));
				}
				else
				{
					double temp = eval(str.substr(i + 1, index - i - 2));
					str.replace(i, index - i, std::to_string(temp));
					index = i + std::to_string(temp).size();
					return(index - (std::to_string(temp).length()));
				}
			}
		}
	}
	else { return index; }
}

int coefficient(std::string& input, int index) {
	if (index > 0) {
		int coefficientPos = NumberIndexRequest(input, index, true);
		if (coefficientPos < index) {
			input.insert(index, "*");
			return 1;
		}
		else return 0;
	}
	return 0;
}

double tolerance(double d)
{
	if (fabs(round(d) - d) < 0.00001) {
		if (round(d) == 0) return 0;
		return round(d);
	}
	else {
		return d;
	}
}
