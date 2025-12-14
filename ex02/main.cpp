#include "PmergeMe.hpp"
#include <cstddef>

int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cout << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>" << std::endl, 1);
	if (!merge.verify(av, ac))
<<<<<<< HEAD
		return (1);
	std::cout << "Before:	";
	merge.show(0);
	merge.sortList();
=======
		return (std::cout << "ERROR, some parameters are incorrect or not positive integers" << std::endl, 1);

	merge.runSort(av, ac);

>>>>>>> b795c64 (done na)
	return (0);
}
