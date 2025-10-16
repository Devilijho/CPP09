#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cout << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>", 1);
	if (merge.verify(av) == 1)
		return (std::cout << "ERROR, some parameters are incorrect",1);
	return (0);
}
