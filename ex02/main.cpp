#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>


int main(int ac, char **av)
{
	PmergeMe merge;

	if (ac < 2)
		return (std::cout << "ERROR, correct usage ./PmergeMe <Numbers separated by an empty space>" << std::endl, 1);
	if (!merge.verify(av, ac - 1))
		return (std::cout << "ERROR, some parameters are incorrect or not positive integers" << std::endl, 1);

	merge.sortDeque();
	// std::cout << "Before: ";
	// merge.showDeque();

	// clock_t time = clock(); // I get the time of execution for the Deque
	// merge.sortDeque();
	// time = clock() - time;
	// double s = double(time) / double(CLOCKS_PER_SEC);

	// std::cout << "Time to process a range of " << ac-1 << " elements with std::[Deque] : " << s << " miliseconds" << std::endl;

	// time = clock(); // I get the time of execution for the List
	// merge.sortList();
	// time = clock() - time;
	// s = double(time) / double(CLOCKS_PER_SEC);

	// std::cout << "Time to process a range of " << ac-1 << " elements with std::[List] : " << s << "miliseconds" << std::endl;

	// std::cout << "After: ";
	// merge.showContainer(DEQUE);

	return (0);
}
