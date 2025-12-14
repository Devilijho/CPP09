#include "PmergeMe.hpp"
<<<<<<< HEAD
#include <cstddef>
#include <utility>


PmergeMe::PmergeMe() : lenghtArgs(0)
{
}
=======


// Orthodox Canonical Form
PmergeMe::PmergeMe()
{}
>>>>>>> b795c64 (done na)

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

<<<<<<< HEAD
long long PmergeMe::strToLong(std::string numStr)
=======
// Utility to convert string to int
int PmergeMe::strToInt(std::string numStr)
>>>>>>> b795c64 (done na)
{
	std::istringstream stream(numStr);
	long long val;

	stream >> val;
	return (val);
}

// Input validation and container population
bool PmergeMe::verify(char** av, int ac)
{
	long long converted;

	lenghtArgs = ac - 1;
	for (size_t i = 1; i <= lenghtArgs; i++)
	{
<<<<<<< HEAD
		converted = strToLong(std::string(av[i]));
		if (converted <= 0 )
			return (std::cout << "Number must be positive", false);
		else if (converted > INT_MAX )
			return (std::cout << "Number must be an int", false);
		list.push_back(converted);
		deque.push_back(converted);
=======
        // Simple check for non-digit characters
        std::string s(av[i]);
        if (s.empty()) return false;
        for (size_t j = 0; j < s.length(); ++j) {
            if (!std::isdigit(s[j])) {
                return false;
            }
        }

		converted = strToInt(s);
		if (converted <= 0) // Constraint: "positive integer sequence" [cite: 229]
			return false;

        // Populate both containers
		list.push_back(converted);
        deque.push_back(converted);
>>>>>>> b795c64 (done na)
	}
	return true;
}

<<<<<<< HEAD
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
	std::cout << std::endl;
}

void copyRange(std::list<size_t> list, size_t start, size_t end)
{
	std::list<size_t>::iterator it;
	for (it = list.begin(); it != list.end(); it++)
	{


	}
}

void PmergeMe::divideList(int order)
{
	if (order == 1)
		return ;
	else
	{
		std::list<size_t> list_r, list_l;


		return (divideList(order-1), divideList(order -1));
	}
}

void PmergeMe::sortList()
{
	std::cout << lenghtArgs << " Numbers in total" << std::endl;
	divideList(lenghtArgs); // supposing arguments are pair

	std::cout << "Sort done lmao" << std::endl;
}

// std::list<std::pair<size_t, size_t> > pairs;

	// std::list<size_t>::iterator it;
	// for (it = list.begin(); it != list.end(); it++)
	// {
	// 	std::pair<size_t, size_t> pair;
	// 	pair.first = *it;
	// 	pair.second = *(++it);
	// 	pairs.push_back(pair);
	// }
=======
// --- Helper Functions ---

// Function to print a container
template<typename T>
void PmergeMe::printContainer(const T& container, const std::string& prefix) const {
    std::cout << prefix;
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Explicit template instantiation for the types used in this file
template void PmergeMe::printContainer<std::list<size_t> >(const std::list<size_t>& container, const std::string& prefix) const;
template void PmergeMe::printContainer<std::deque<size_t> >(const std::deque<size_t>& container, const std::string& prefix) const;

// Generates Jacobsthal numbers up to a limit n (for insertion sequence)
std::vector<int> PmergeMe::getJacobsthal(int n) const {
    std::vector<int> jacobsthal;
    int j_prev = 1;
    int j_curr = 3;

    // The sequence for indices: 1, 2, 4, 6, 11, 21, ...
    // J(n) = J(n-1) + 2*J(n-2). We only care about the values.
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

// --- List Implementation of Ford-Johnson Sort ---

// Step 1: Sort the pairs based on the larger element (the main chain)
void PmergeMe::sortPairsList(std::list<std::list<size_t> >& pairs) {
    // This uses a list-friendly insertion sort based on the second element (the largest) of each inner list (pair).
    for (std::list<std::list<size_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it == pairs.begin()) continue;

        std::list<std::list<size_t> >::iterator prev = it;
        --prev;

        // Manual insertion sort logic
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


// Step 3 (cont.): Insertion Sort of pending elements using Jacobsthal
void PmergeMe::insertionSortList(std::list<size_t>& main_chain, std::list<size_t>& pend_elements) {
    if (pend_elements.empty()) return;

    std::vector<int> jacobsthal = getJacobsthal(pend_elements.size() + 1);

    int prev_jacobsthal = 1;

    // Start from t2 (index 2 in the sequence: Jacobsthal[i] = 2)
    for (size_t i = 1; i < jacobsthal.size(); ++i) {
        int next_jacobsthal = jacobsthal[i];

        // Insert elements in the range (t_{i-1}, t_i] in reverse order
        for (int j = std::min(next_jacobsthal, (int)pend_elements.size()) - 1; j >= prev_jacobsthal; --j) {

            std::list<size_t>::iterator pend_it = pend_elements.begin();
            // std::advance is O(N) but necessary for list random access
            for (int k = 0; k < j; ++k)
                ++pend_it;
            size_t element_to_insert = *pend_it;

            // Perform binary search insertion (manual lower_bound for list)
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

// Step 2 & 3: Merge and Insert
void PmergeMe::mergeSortList(std::list<std::list<size_t> >& pairs, size_t straggler) {
    std::list<size_t> main_chain;
    std::list<size_t> pend_elements;

    // Populate main_chain (B) and pend_elements (A)
    for (std::list<std::list<size_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        main_chain.push_back(it->back());
        pend_elements.push_back(it->front());
    }

    // Insert p1 (the first pending element) at the beginning of the main chain.
    if (!pend_elements.empty()) {
        main_chain.push_front(pend_elements.front());
        pend_elements.pop_front();
    }

    // Step 3: Insert the remaining pending elements using Jacobsthal sequence
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


// The main entry point for the list sort (Overloaded method)
void PmergeMe::mergeInsertSort(std::list<size_t>& container) {
    if (container.size() < 2) return;

    // 1. Create pairs and sort each pair
    std::list<std::list<size_t> > pairs;
    size_t straggler = 0;

    // Handle the straggler element (odd number of elements)
    if (container.size() % 2 != 0) {
        straggler = container.back();
        container.pop_back(); // Remove the straggler for now
    }

    std::list<size_t>::iterator it = container.begin();
    // Create and sort pairs
    for (; it != container.end(); ) {
        std::list<size_t> pair;
        size_t a = *it++;
        size_t b = *it++;

        // Sort the pair
        if (a > b) {
            pair.push_back(b);
            pair.push_back(a);
        } else {
            pair.push_back(a);
            pair.push_back(b);
        }
        pairs.push_back(pair);
    }

    // 2. Sort the pairs based on the larger element
    sortPairsList(pairs);

    // 3. Merge the pairs and insert the pending elements
    mergeSortList(pairs, straggler);
}


// --- Deque Implementation of Ford-Johnson Sort ---

// Step 1: Sort the pairs based on the larger element
void PmergeMe::sortPairsDeque(std::deque<std::deque<size_t> >& pairs) {
    // Insertion sort using random access iterators/indices
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


// Step 3 (cont.): Insertion Sort of pending elements using Jacobsthal
void PmergeMe::insertionSortDeque(std::deque<size_t>& main_chain, std::deque<size_t>& pend_elements) {
    if (pend_elements.empty()) return;

    std::vector<int> jacobsthal = getJacobsthal(pend_elements.size() + 1);

    int prev_jacobsthal = 1;

    for (size_t i = 1; i < jacobsthal.size(); ++i) {
        int next_jacobsthal = jacobsthal[i];

        // Insert elements in the range (t_{i-1}, t_i] in reverse order
        for (int j = std::min(next_jacobsthal, (int)pend_elements.size()) - 1; j >= prev_jacobsthal; --j) {

            size_t element_to_insert = pend_elements[j];

            // Binary search insertion (std::lower_bound works efficiently for deque)
            std::deque<size_t>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), element_to_insert);
            main_chain.insert(pos, element_to_insert);
        }
        prev_jacobsthal = next_jacobsthal;
    }
}

// Step 2 & 3: Merge and Insert
void PmergeMe::mergeSortDeque(std::deque<std::deque<size_t> >& pairs, size_t straggler) {
    std::deque<size_t> main_chain;
    std::deque<size_t> pend_elements;

    // Populate main_chain and pend_elements
    for (size_t i = 0; i < pairs.size(); ++i) {
        main_chain.push_back(pairs[i].back());
        pend_elements.push_back(pairs[i].front());
    }

    // Insert p1 (the first pending element) at the beginning of the main chain.
    if (!pend_elements.empty()) {
        main_chain.push_front(pend_elements.front());
        pend_elements.pop_front();
    }

    // Step 3: Insert the remaining pending elements using Jacobsthal sequence
    insertionSortDeque(main_chain, pend_elements);

    // Insert the straggler element (if any)
    if (straggler != 0) {
        std::deque<size_t>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(pos, straggler);
    }

    deque.swap(main_chain);
}


// The main entry point for the deque sort (Overloaded method)
void PmergeMe::mergeInsertSort(std::deque<size_t>& container) {
    if (container.size() < 2) return;

    // 1. Create pairs and sort each pair
    std::deque<std::deque<size_t> > pairs;
    size_t straggler = 0;

    // Handle the straggler element (odd number of elements)
    if (container.size() % 2 != 0) {
        straggler = container.back();
        container.pop_back(); // Remove the straggler for now
    }

    // Create and sort pairs
    for (size_t i = 0; i < container.size(); i += 2) {
        std::deque<size_t> pair;
        size_t a = container[i];
        size_t b = container[i + 1];

        // Sort the pair
        if (a > b) {
            pair.push_back(b);
            pair.push_back(a);
        } else {
            pair.push_back(a);
            pair.push_back(b);
        }
        pairs.push_back(pair);
    }

    // 2. Sort the pairs based on the larger element
    sortPairsDeque(pairs);

    // 3. Merge the pairs and insert the pending elements
    mergeSortDeque(pairs, straggler);
}


// --- Main Execution Function ---

void PmergeMe::runSort(char** av, int ac) {

    int num_elements = ac - 1;

    // --- Initial output ---
    std::cout << "Before: ";
    for (int i = 1; i < ac; ++i) {
        std::cout << av[i] << (i == ac - 1 ? "" : " ");
    }
    std::cout << std::endl; // [cite: 241]

    // --- Sort with std::list and measure time ---
    // The subject advises performing all operations, including data management, within the time measurement. [cite: 270]
    clock_t start_list = clock();
    mergeInsertSort(list);
    clock_t end_list = clock();
    double time_list = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC * 1000000.0; // In microseconds

    // --- Sort with std::deque and measure time ---
    clock_t start_deque = clock();
    mergeInsertSort(deque);
    clock_t end_deque = clock();
    double time_deque = static_cast<double>(end_deque - start_deque) / CLOCKS_PER_SEC * 1000000.0; // In microseconds

    // --- Final output ---
    std::cout << "After: ";
    // Use the list as the 'After' sequence for display (they should be identical) [cite: 242]
    printContainer(list, "");

    // Output time for the first container [cite: 243]
    std::cout << "Time to process a range of " << num_elements << " elements with std::list : "
              << std::fixed << std::setprecision(5) << time_list << " us" << std::endl;

    // Output time for the second container [cite: 244]
    std::cout << "Time to process a range of " << num_elements << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << time_deque << " us" << std::endl;
}
>>>>>>> b795c64 (done na)
