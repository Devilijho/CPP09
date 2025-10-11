#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <sstream>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		bool verify(char *input);
		void build();

		int strToInt(std::string numStr);
		float strToFloat(std::string numStr);
	private:
		std::string input;
		std::stack<int> stack;
};
