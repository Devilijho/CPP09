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
		return (std::cout << "ERROR, parenthesis not allowed " << std::endl,false);

	while(stream >> word)
	{
		if (word[0] > '9' || word[0] < '0') // if first char of word is not a number
		{
			if (word.size() > 1 || (word[0] != '*' && word[0] != '/' && word[0] != '-' && word[0] != '+')) // if its differente than any valid operator or is longer than 1 == error
				return (std::cout << "ERROR, operator " << word << " not valid" << std::endl, false);
		}
		else // it is a number
		{
			if (strToInt(word) != strToFloat(word))
				return (std::cout << "ERROR, floats not valid" << std::endl, false);
			if (findNonDigits(word))
				return (std::cout << "ERROR, number must be compossed of only digits from 0-9" << std::endl, false);
		}
	}
	return true;
}

void RPN::calculate()
{
	std::istringstream stream(input);
	std::string word;
	int	result, num1, num2;

	while (stream >> word)
	{
		if (word[0] <= '9' && word[0] >= '0')//is a number
		{
			stack.push(strToInt(word));
		}
		else//is a operator
		{
			num1 = stack.top();
			stack.pop();
			num2 = stack.top();
			stack.pop();
			switch (word[0])
			{
				case '+':
					result = num1 + num2; break;
				case '-':
				result = num2 - num1; break;
				case '*':
					result = num1 * num2; break;
				case '/':
					result = num2 / num1; break;
			}
			stack.push(result);
		}
	}
	std::cout << stack.top() << std::endl;
}

bool RPN::findNonDigits(std::string numStr)
{
	for (size_t i = 0; i < numStr.size() ; i++)
	{
		if (numStr[i] < '0' || numStr[i] > '9')
			return true;
	}
	return false;
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
