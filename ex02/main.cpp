#include "PmergeMe.hpp"
#include <cstddef>

int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cout << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>", 1);
	if (!merge.verify(av, ac))
		return (1);
	std::cout << "Before:	";
	merge.show(0);
	merge.sortList();
	return (0);
}
