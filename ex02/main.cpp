#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cout << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>" << std::endl, 1);
	if (!merge.verify(av, ac))
		return (std::cout << "ERROR, some parameters are incorrect or not positive integers" << std::endl, 1);

	merge.runSort(av, ac);

	return (0);
}
