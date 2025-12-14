#include "PmergeMe.hpp"

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
		std::string s(av[i]);
		if (s.empty()) return false;
		for (size_t j = 0; j < s.length(); ++j) {
			if (!std::isdigit(s[j])) {
				return false;
			}
		}

		converted = strToInt(s);
		if (converted <= 0)
			return false;

		list.push_back(converted);
		deque.push_back(converted);
	}
	return true;
}

template<typename T>
void PmergeMe::printContainer(const T& container, const std::string& prefix) const {
	std::cout << prefix;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template void PmergeMe::printContainer<std::list<size_t> >(const std::list<size_t>& container, const std::string& prefix) const;
template void PmergeMe::printContainer<std::deque<size_t> >(const std::deque<size_t>& container, const std::string& prefix) const;

std::vector<int> PmergeMe::getJacobsthal(int n) const {
	std::vector<int> jacobsthal;
	int j_prev = 1;
	int j_curr = 3;

	if (n >= 1) jacobsthal.push_back(1);
	if (n >= 2) jacobsthal.push_back(2);

	while (j_curr < n) {
		jacobsthal.push_back(j_curr);
		int j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
	}
	return jacobsthal;
}

void PmergeMe::sortPairsList(std::list<std::list<size_t> >& pairs) {
	for (std::list<std::list<size_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
		if (it == pairs.begin()) continue;

		std::list<std::list<size_t> >::iterator prev = it;
		--prev;

		while (it != pairs.begin() && prev->back() > it->back()) {
			std::list<size_t> temp = *it;
			*it = *prev;
			*prev = temp;

			it = prev;
			if (it == pairs.begin()) break;
			prev = it;
			--prev;
		}
	}
}

void PmergeMe::insertionSortList(std::list<size_t>& main_chain, std::list<size_t>& pend_elements) {
	if (pend_elements.empty()) return;

	std::vector<int> jacobsthal = getJacobsthal(pend_elements.size() + 1);

	int prev_jacobsthal = 1;

	for (size_t i = 1; i < jacobsthal.size(); ++i) {
		int next_jacobsthal = jacobsthal[i];

		for (int j = std::min(next_jacobsthal, (int)pend_elements.size()) - 1; j >= prev_jacobsthal; --j) {

			std::list<size_t>::iterator pend_it = pend_elements.begin();
			for (int k = 0; k < j; ++k)
				++pend_it;
			size_t element_to_insert = *pend_it;

			std::list<size_t>::iterator it = main_chain.begin();
			for (; it != main_chain.end(); ++it) {
				if (*it >= element_to_insert) {
					break;
				}
			}
			main_chain.insert(it, element_to_insert);
		}
		prev_jacobsthal = next_jacobsthal;
	}
}

void PmergeMe::mergeSortList(std::list<std::list<size_t> >& pairs, size_t straggler) {
	std::list<size_t> main_chain;
	std::list<size_t> pend_elements;

	for (std::list<std::list<size_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
		main_chain.push_back(it->back());
		pend_elements.push_back(it->front());
	}

	if (!pend_elements.empty()) {
		main_chain.push_front(pend_elements.front());
		pend_elements.pop_front();
	}

	insertionSortList(main_chain, pend_elements);

	// Insert the straggler element (if any)
	if (straggler != 0) {
		std::list<size_t>::iterator it = main_chain.begin();
		for (; it != main_chain.end(); ++it) {
			if (*it > straggler) {
				break;
			}
		}
		main_chain.insert(it, straggler);
	}

	list.swap(main_chain);
}


void PmergeMe::mergeInsertSort(std::list<size_t>& container) {
	if (container.size() < 2) return;

	std::list<std::list<size_t> > pairs;
	size_t straggler = 0;

	if (container.size() % 2 != 0) {
		straggler = container.back();
		container.pop_back();
	}

	std::list<size_t>::iterator it = container.begin();
	for (; it != container.end(); ) {
		std::list<size_t> pair;
		size_t a = *it++;
		size_t b = *it++;

		if (a > b) {
			pair.push_back(b);
			pair.push_back(a);
		} else {
			pair.push_back(a);
			pair.push_back(b);
		}
		pairs.push_back(pair);
	}

	sortPairsList(pairs);

	mergeSortList(pairs, straggler);
}

void PmergeMe::sortPairsDeque(std::deque<std::deque<size_t> >& pairs)
{
	for (size_t i = 1; i < pairs.size(); ++i) {
		std::deque<size_t> currentPair = pairs[i];
		int j = i - 1;
		while (j >= 0 && pairs[j].back() > currentPair.back()) {
			pairs[j + 1] = pairs[j];
			j--;
		}
		pairs[j + 1] = currentPair;
	}
}


void PmergeMe::insertionSortDeque(std::deque<size_t>& main_chain, std::deque<size_t>& pend_elements)
{
	if (pend_elements.empty()) return;

	std::vector<int> jacobsthal = getJacobsthal(pend_elements.size() + 1);

	int prev_jacobsthal = 1;

	for (size_t i = 1; i < jacobsthal.size(); ++i) {
		int next_jacobsthal = jacobsthal[i];

		for (int j = std::min(next_jacobsthal, (int)pend_elements.size()) - 1; j >= prev_jacobsthal; --j) {

			size_t element_to_insert = pend_elements[j];

			std::deque<size_t>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), element_to_insert);
			main_chain.insert(pos, element_to_insert);
		}
		prev_jacobsthal = next_jacobsthal;
	}
}

void PmergeMe::mergeSortDeque(std::deque<std::deque<size_t> >& pairs, size_t straggler)
{
	std::deque<size_t> main_chain;
	std::deque<size_t> pend_elements;

	for (size_t i = 0; i < pairs.size(); ++i) {
		main_chain.push_back(pairs[i].back());
		pend_elements.push_back(pairs[i].front());
	}

	if (!pend_elements.empty()) {
		main_chain.push_front(pend_elements.front());
		pend_elements.pop_front();
	}

	insertionSortDeque(main_chain, pend_elements);

	if (straggler != 0) {
		std::deque<size_t>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
		main_chain.insert(pos, straggler);
	}

	deque.swap(main_chain);
}

void PmergeMe::mergeInsertSort(std::deque<size_t>& container) {
	if (container.size() < 2) return;

	std::deque<std::deque<size_t> > pairs;
	size_t straggler = 0;

	if (container.size() % 2 != 0) {
		straggler = container.back();
		container.pop_back();
	}

	for (size_t i = 0; i < container.size(); i += 2) {
		std::deque<size_t> pair;
		size_t a = container[i];
		size_t b = container[i + 1];

		if (a > b)
		{
			pair.push_back(b);
			pair.push_back(a);
		}
		else
	 	{
			pair.push_back(a);
			pair.push_back(b);
		}
		pairs.push_back(pair);
	}

	sortPairsDeque(pairs);
	mergeSortDeque(pairs, straggler);
}

void PmergeMe::runSort(char** av, int ac) {

	int num_elements = ac - 1;

	std::cout << "Before: ";
	for (int i = 1; i < ac; ++i) {
		std::cout << av[i] << (i == ac - 1 ? "" : " ");
	}
	std::cout << std::endl;

	clock_t start_list = clock();
	mergeInsertSort(list);
	clock_t end_list = clock();
	double time_list = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC * 1000000.0;

	clock_t start_deque = clock();
	mergeInsertSort(deque);
	clock_t end_deque = clock();
	double time_deque = static_cast<double>(end_deque - start_deque) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "After: ";
	printContainer(list, "");

	std::cout << "Time to process a range of " << num_elements << " elements with std::list : "
			  << std::fixed << std::setprecision(5) << time_list << " us" << std::endl;

	std::cout << "Time to process a range of " << num_elements << " elements with std::deque : "
			  << std::fixed << std::setprecision(5) << time_deque << " us" << std::endl;
}
