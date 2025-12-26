#include "RPN.hpp"


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
	unsigned int count_operators = 0, count_numbers = 0;

	this->input = std::string(input);
	if ((std::string::npos != this->input.find('(', 0)) || (std::string::npos != this->input.find(')', 0)))
		return (std::cerr << "ERROR, parenthesis not allowed " << std::endl,false);

	while(stream >> word)
	{
		if (findNonDigits(word) && strToInt(word) == 0) // if it contains non digit return true
		{
			if (word.size() > 1 || (word[0] != '*' && word[0] != '/' && word[0] != '-' && word[0] != '+')) // if its differente than any valid operator or is longer than 1 == error
				return (std::cerr << "ERROR, operator " << word << " not valid" << std::endl, false);
			count_operators++;
		}
		else // it is a number
		{
			int strInt = strToInt(word);
			if (strInt != strToFloat(word))
				return (std::cerr << "ERROR, floats not valid" << std::endl, false);
			if (strInt > 9)
				return (std::cerr << "ERROR, number must be a single digit" << std::endl, false);
			if (strInt < 0)
				return (std::cerr << "ERROR, number must be positive" << std::endl, false);
			if (findNonDigits(word))
				return (std::cerr << "ERROR, number must be compossed of only digits from 0-9" << std::endl, false);
			count_numbers++;
		}
	}
	if (count_numbers - 1 != count_operators)
		return (std::cerr << "Error, not enough operators (or too many)" << std::endl, false);
	return true;
}

void RPN::calculate()
{
	std::istringstream stream(input);
	std::string word;
	int	result, num1, num2;

	while (stream >> word)
	{
		// std::cout << word << std::endl;
		if (word[0] <= '9' && word[0] >= '0')//is a number
		{
			stack.push(strToInt(word));
		}
		else//is a operator
		{
			if (stack.size() < 2)
			{
				std::cerr << "ERROR, not enough operands" << std::endl;
				exit(1);
			}
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
					if (num1 == 0)
					{
						std::cerr << "ERROR, cannot divide by 0" << std::endl;
						exit(1);
					}
					result = num2 / num1;
				 	break;
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
