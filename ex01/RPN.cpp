#include "RPN.hpp"
#include <sstream>

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &other)
{
	this->input = other.input;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->input = other.input;
	}
	return (*this);
}

bool RPN::verify(char *input)
{
	bool found;
	this->input = std::string(input);

	found = ((std::string::npos != this->input.find('(', 0)) || (std::string::npos != this->input.find(')', 0)));



	return found;
}

float RPN::strToFloat(std::string numStr)
{
	float val;
	std::istringstream stream(numStr);

	stream >> val;
	return (val);
}

int RPN::strToInt(std::string numStr)
{
	std::istringstream stream(numStr);
	int val;

	stream >> val;
	return (val);
}
