#include "PmergeMe.hpp"
#include <cstddef>
#include <iterator>
#include <unistd.h>
#include <vector>

PmergeMe::PmergeMe()
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	this->list = other.list;
	this->deque = other.deque;
	this->lenghtArgs = other.lenghtArgs;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->list = other.list;
		this->deque = other.deque;
		this->lenghtArgs = other.lenghtArgs;
	}
	return (*this);
}

int PmergeMe::strToInt(std::string numStr)
{
	std::stringstream stream(numStr);
	int val;

	stream >> val;
	return (val);
}

std::string PmergeMe::intToStr(int num)
{
	std::stringstream ss;
	ss << num;
	std::string str = ss.str();
	return str;
}

bool PmergeMe::verify(char **av, int ac)
{
	lenghtArgs = ac - 1;
	for (int i = 1; i <= ac; ++i)
	{
		std::string numStr(av[i]);
		int num = strToInt(numStr);
		if (num < 0)
		{
			std::cout << "Parameter : " << num << " is negative" << std::endl;
			return false;
		}
		std::string tmpStr = intToStr(num);
		if (numStr != tmpStr)
		{
			std::cout << numStr << " != " << tmpStr << std::endl;
			return false;
		}
		list.push_back(num);
		deque.push_back(num);
	}
	return true;
}

void PmergeMe::showList(std::list<size_t> list)
{
	std::list<size_t>::iterator it = list.begin();
	while (it != list.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}

void PmergeMe::showDeque(std::deque<size_t> deque)
{
	std::deque<size_t>::iterator it = deque.begin();
	while (it != deque.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}


void PmergeMe::createDeques(std::deque< std::deque <size_t> > &sets, size_t order)
{
	size_t index = 0;
	std::deque<size_t> temp;
	while (index < deque.size())
	{
		for (size_t subIndex = 0; subIndex < order; subIndex++)
		{
			temp.push_back(deque[index + subIndex]);
		}
		sets.push_back(temp);
		temp.clear();
		index += order;
	}
}

void PmergeMe::sortSubDeques(std::deque< std::deque <size_t> > &sets, size_t order)
{
	size_t last_first, last_second;
	std::deque< std::deque <size_t> > newSet;
	size_t i = 0;

	while (i + 1 < sets.size() && sets[i].size() == sets[i + 1].size()) // I check if i can access next value and if i both deques have the same size
	{
		last_first = sets[i][order - 1];
		last_second = sets[i + 1][order - 1];
		if (last_first > last_second)
		{
			sets[i + 1].insert(sets[i + 1].end(),sets[i].begin(), sets[i].end());
			//showDeque(sets[i + 1]);
			newSet.push_back(sets[i+1]);
		}
		else
		{
			sets[i].insert(sets[i].end(), sets[i + 1].begin(), sets[i + 1].end());
			//showDeque(sets[i]);
			newSet.push_back(sets[i]);
		}
		i += 2;
	}
	if (i != sets.size()) // we have an extra deque
	{
		if (i + 1 < sets.size())
			sets[i].insert(sets[i].end(), sets[i+1].begin(), sets[i+1].end()); // if we had alr an extra deque we concatanate that one to the actual extra
		//showDeque(sets[i]);
		newSet.push_back(sets[i]);
	}
	sets = newSet;
}

void PmergeMe::sortDeque()
{
	std::deque< std::deque <size_t> > sets;
	size_t order = 1;

	createDeques(sets, order);
	while (order <= (lenghtArgs / 2) + 1)
	{
		sortSubDeques(sets, order);
		order <<= 1;
	}
	for (size_t i = 0; i < sets.size(); i++)
	{
		showDeque(sets[i]);
	}
}


		// for (size_t i = 0; i< sets.size(); i++)
		// {
		// 	for (size_t x = 0; x < sets[i].size(); x++)
		// 	{
		// 		std::cout << sets[i][x] << " ";
		// 	}
		// 	std::cout << std::endl;
		// }
void PmergeMe::sortList()
{
}
