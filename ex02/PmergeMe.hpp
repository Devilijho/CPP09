#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <list>
#include <deque>
#include <string>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <cstddef>
#include <ctime>
#include <iomanip>


#define DEQUE 0
#define LIST 1

#define WINNER 'a'
#define LOSER 'b'
#define NONE 'x'

#define DEBUG 0
#define SHOW 1

struct Number
{
	size_t	val;
	char	state;
	size_t	pos;
	size_t partner;

	bool operator<(const Number& other) const;
	bool operator==(const Number& other) const;
};

class PmergeMe {

	private:
		size_t lenghtArgs;

		std::list<Number> list;
		std::deque<Number> deque;


	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe &operator=(const PmergeMe&);

		bool verify(char** av, int ac);
		int strToInt(std::string numStr);
		std::string intToStr(int num);

		std::deque<Number> recursiveSortDeque(std::deque<Number>);
		void insertLosers(std::deque<Number> &sorted, std::deque<Number> losers);
		void assignLosersDeque(std::deque<Number> &sorted, std::deque<Number> &losers, Number &straggler);
		double sortDeque();


		void insertLosers(std::list<Number> &sorted, std::list<Number> losers);
		std::list<Number> recursiveSortList(std::list<Number> c_list);
		void assignLosersList(std::list<Number> &sorted, std::list<Number> &losers, Number &straggler);
		Number &getNumberList(size_t pos, std::list<Number> &list);
		double sortList();

		size_t	jacobsthal(int order);

		void showList(std::list<Number> list);
		void showDeque(std::deque<Number> deque);
		void showSelf(int which);
		void verifySort(int which);


};
