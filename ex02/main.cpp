#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cerr << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>" << std::endl, 1);
	if (!merge.verify(av, ac - 1))
		return (std::cerr << "ERROR, some parameters are incorrect or not positive integers" << std::endl, 1);


	if (SHOW)
	{
		std::cout << "Before: ";
		merge.showSelf(DEQUE);
	}

	double elapsed_d = merge.sortDeque();
	double elapsed_l = merge.sortList();


	if (SHOW)
	{
		std::cout << "After: ";
		merge.showSelf(DEQUE);
		// merge.showSelf(LIST);
	}

	std::cout << "Time to process a range of " << ac-1 << " elements with std::[Deque] : " << std::fixed << std::setprecision(0) << elapsed_d << " us" << std::endl;
	std::cout << "Time to process a range of " << ac-1 << " elements with std::[List] : " << std::fixed << std::setprecision(0) << elapsed_l << " us" << std::endl;

	// merge.verifySort(DEQUE);
	// merge.verifySort(LIST);
	return (0);
}
