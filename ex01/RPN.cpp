#include "RPN.hpp"
#include <cstdlib>
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
	std::istringstream stream((std::string(input)));
	std::string word;

	this->input = std::string(input);
	if ((std::string::npos != this->input.find('(', 0)) || (std::string::npos != this->input.find(')', 0)))
		return (std::cout << "ERROR, parenthesis not allowed ",false);

	while(stream >> word)
	{
		if (word[0] > '9' || word[0] < '0') // if first char of word is not a number
		{
			if (word.size() > 1 || (word[0] != '*' && word[0] != '/' && word[0] != '-' && word[0] != '+')) // if its differente than any valid operator or is longer than 1 == error
				return (std::cout << "ERROR, operator " << word << " not valid" << std::endl, false);
			else // its a valid operator
				this->stack.push(word[0]);;
		}
		else // it is a number
			this->stack.push(strToInt(word));
	}
	return true;
}

void RPN::build()
{

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
