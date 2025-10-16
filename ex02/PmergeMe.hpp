#pragma once

#include <iostream>
#include <list>
#include <string>
#include <sstream>

class PmergeMe{

	private:
		int lenghtArgs;

		std::list<size_t> list;
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

		bool verify(char**, int);
		int strToInt(std::string numStr);
};
