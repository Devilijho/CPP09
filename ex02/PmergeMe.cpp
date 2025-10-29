#include "PmergeMe.hpp"
#include <climits>
#include <cstddef>
#include <string>

PmergeMe::PmergeMe() : lenghtArgs(0)
{
}

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

long long PmergeMe::strToLong(std::string numStr)
{
	std::istringstream stream(numStr);
	long long val;

	stream >> val;
	return (val);
}

bool PmergeMe::verify(char** av, int ac)
{
	long long converted;

	lenghtArgs = ac - 1;
	for (size_t i = 1; i <= lenghtArgs; i++)
	{
		converted = strToLong(std::string(av[i]));
		if (converted <= 0 )
			return (std::cout << "Number must be positive", false);
		else if (converted > INT_MAX )
			return (std::cout << "Number must be an int", false);
		list.push_back(converted);
		deque.push_back(converted);
	}
	return true;
}

void PmergeMe::show(size_t containerID)
{
	if (containerID == LIST)
	{
		std::copy(list.begin(), list.end(),
		std::ostream_iterator<int>(std::cout, " "));
	}
	else if (containerID == DEQUE)
	{
		std::copy(deque.begin(), deque.end(),
		std::ostream_iterator<int>(std::cout, " "));
	}
}

void PmergeMe::sort()
{

	std::cout << "Sort done lmao" << std::endl;
}
