#pragma once

#include <array>
#include <cstddef>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <deque>
#include <string>
#include <sstream>
<<<<<<< HEAD
#include <cstddef>
#include <utility>
#include <climits>
#include <set>


#define LIST 0
#define DEQUE 1
=======
#include <ctime>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
>>>>>>> b795c64 (done na)

class PmergeMe {

	private:
		size_t lenghtArgs;

<<<<<<< HEAD
		std::list<size_t> list; //listo
		std::deque<size_t> deque; //deck
=======
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

>>>>>>> b795c64 (done na)
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

<<<<<<< HEAD
		void divideList(int order);
		bool verify(char**, int);
		long long strToLong(std::string numStr);
		void sortList();
		void show(size_t);
		void subSort();
=======
		bool verify(char** av, int ac);
		int strToInt(std::string numStr);

		void runSort(char** av, int ac);
>>>>>>> b795c64 (done na)
};
