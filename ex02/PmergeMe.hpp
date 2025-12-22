#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>

#define DEQUE 0
#define LIST 1


class PmergeMe {

	private:
		size_t lenghtArgs;

		std::list<size_t> list;
		std::deque<size_t> deque;


	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

		bool verify(char** av, int ac);
		int strToInt(std::string numStr);
		std::string intToStr(int num);
		void sortDeque();
		void sortList();

		void createDeques(std::deque< std::deque <size_t> > &sets, size_t order);
		void sortSubDeques(std::deque< std::deque <size_t> > &sets, size_t order);
		void showList(std::list<size_t> list);
		void showDeque(std::deque<size_t> deque);


};
