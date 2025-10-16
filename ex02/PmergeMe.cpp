#include "PmergeMe.hpp"
#include <string>

PmergeMe::PmergeMe()
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	this->list = other.list;
	this->lenghtArgs = other.lenghtArgs;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->list = other.list;
		this->lenghtArgs = other.lenghtArgs;
	}
	return (*this);
}

int PmergeMe::strToInt(std::string numStr)
{
	std::istringstream stream(numStr);
	int val;

	stream >> val;
	return (val);
}

bool PmergeMe::verify(char** av, int ac)
{
	int converted;

	lenghtArgs = ac;
	for (int i = 1; i < lenghtArgs; i++)
	{
		converted = strToInt(std::string(av[i]));
		if (converted <= 0)
			return false;
		list.push_back(converted);
	}
	return true;
}
