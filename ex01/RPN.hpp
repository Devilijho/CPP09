#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cstdlib>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		bool verify(char *input);
		void calculate();

		int strToInt(std::string numStr);
		float strToFloat(std::string numStr);
		bool findNonDigits(std::string numStr);
	private:
		std::string input;
		std::stack<int> stack;
};
