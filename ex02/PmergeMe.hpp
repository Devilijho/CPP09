#pragma once

#include <array>
#include <cstddef>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <sstream>
#include <cstddef>
#include <utility>
#include <climits>
#include <set>


#define LIST 0
#define DEQUE 1

class PmergeMe{

	private:
		size_t lenghtArgs;

		std::list<size_t> list; //listo
		std::deque<size_t> deque; //deck
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

		bool verify(char**, int);
		long long strToLong(std::string numStr);
		void sortList();
		void show(size_t);
		void subSort();
};
