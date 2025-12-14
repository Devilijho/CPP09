#pragma once

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

class PmergeMe {

	private:
		int lenghtArgs;

		std::list<size_t> list;
		std::deque<size_t> deque;

		void mergeInsertSort(std::list<size_t>& container);
		void mergeInsertSort(std::deque<size_t>& container);

		template<typename T>
		void printContainer(const T& container, const std::string& prefix) const;

		std::vector<int> getJacobsthal(int n) const;

		void sortPairsList(std::list<std::list<size_t> >& pairs);
		void mergeSortList(std::list<std::list<size_t> >& pairs, size_t straggler);
		void insertionSortList(std::list<size_t>& main_chain, std::list<size_t>& pend_elements);

		void sortPairsDeque(std::deque<std::deque<size_t> >& pairs);
		void mergeSortDeque(std::deque<std::deque<size_t> >& pairs, size_t straggler);
		void insertionSortDeque(std::deque<size_t>& main_chain, std::deque<size_t>& pend_elements);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

		bool verify(char** av, int ac);
		int strToInt(std::string numStr);

		void runSort(char** av, int ac);
};
