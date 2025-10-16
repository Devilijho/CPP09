#pragma once

#include <iostream>
#include <string>

class PmergeMe{

	private:
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe *operator=(const PmergeMe &other);
};
