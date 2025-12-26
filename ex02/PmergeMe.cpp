#include "PmergeMe.hpp"


bool Number::operator<(const Number& other) const {
        return (this->val < other.val);
    }
bool Number::operator==(const Number& other) const {
	return (this->val < other.val);
        }

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
	std::stringstream stream(numStr);
	int val;

	stream >> val;
	return (val);
}

std::string PmergeMe::intToStr(int num)
{
	std::stringstream ss;
	ss << num;
	std::string str = ss.str();
	return str;
}

bool PmergeMe::verify(char **av, int ac)
{
	lenghtArgs = ac - 1;
	for (int i = 1; i <= ac; ++i)
	{
		std::string numStr(av[i]);
		int num = strToInt(numStr);
		if (num < 0)
		{
			std::cerr << "Parameter : " << num << " is negative" << std::endl;
			return false;
		}
		std::string tmpStr = intToStr(num);
		if (numStr != tmpStr)
		{
			std::cerr << numStr << " != " << tmpStr << std::endl;
			return false;
		}
		Number temp;
		temp.pos = -1;
		temp.state = 'x';
		temp.val = num;
		list.push_back(temp);
		deque.push_back(temp);
	}
	for (size_t i = 0; i < deque.size() - 1; i++)
	{
		for (size_t j = i + 1; j < deque.size(); j++)
		{
			if (deque[i].val == deque[j].val)
			{
				std::cerr << "Duplicates not allowed" << std::endl;
				return false;
			}
		}
	}
	return true;
}

void PmergeMe::showList(std::list<Number> list)
{
	std::list<Number>::iterator it = list.begin();
	while (it != list.end())
	{
		std::cout << it->val << " ";
		it++;
	}
	std::cout << std::endl;
}

void PmergeMe::showDeque(std::deque<Number> deque)
{
	std::deque<Number>::iterator it = deque.begin();
	std::cout << "Showing current deque with " << deque.size() << " elements:" << std::endl;
	while (it != deque.end())
	{
		std::cout << it->val << " ";
		it++;
	}
	std::cout << std::endl;
}



size_t	PmergeMe::jacobsthal(int order)
{
	if (order < 2)
		return 1;
	else
		return (jacobsthal(order - 1) + 2 * jacobsthal(order - 2 ));
}

void PmergeMe::insertLosers(std::deque<Number> &sorted, std::deque<Number> losers)
{
	sorted.push_front(losers[0]); // b1 always go before a1
	size_t jacob_k = 2, range_start, range_end, inserted_elements = 1;// jacobsthal step starting at two since we alr did for j(1) = 1

	while (inserted_elements < losers.size()) // we want to add all elements from losers to winners
	{
		range_start = jacobsthal(jacob_k);// j(k)
		if (range_start > losers.size())
			range_start = losers.size();

		range_end = jacobsthal(jacob_k - 1); // j(k - 1)

		if (DEBUG)
			std::cout << "Current jacob step : " << jacob_k << " , going from : " << range_start << " to " << range_end << std::endl;
		while (range_start > range_end)
		{
			Number act_loser = losers[range_start - 1]; // bcs we go from pos i but in a real deque it represents d[i - 1] to not go out of bounds

			std::deque<Number>::iterator it_limit = sorted.begin();
             while (it_limit != sorted.end())
            {
                 if (it_limit->val == act_loser.partner)
                     break;
                 it_limit++;
            }
			std::deque<Number>::iterator it_pos = std::lower_bound(sorted.begin(), it_limit, losers[range_start - 1]);
			sorted.insert(it_pos, act_loser);

			range_start--;
			inserted_elements++;
		}
		jacob_k++;
	}
}


void PmergeMe::assignLosersDeque(std::deque<Number> &sorted, std::deque<Number> &losers, Number &straggler)
{
	std::deque<Number> reorderedLosers;
	for (size_t s = 0; s < sorted.size(); s++)
	{
		for (size_t l = 0; l < losers.size(); l++)
		{
			if (sorted[s].val == losers[l].partner)
			{
				reorderedLosers.push_back(losers[l]);
				break ;
			}
		}
	}
	if (straggler.state != NONE)
		reorderedLosers.push_back(straggler);
	losers = reorderedLosers;
}


void PmergeMe::assignLosersList(std::list<Number> &sorted, std::list<Number> &losers, Number &straggler)
{
	std::list<Number> reorderedLosers;
	for (size_t s = 0; s < sorted.size(); s++)
	{
		for (size_t l = 0; l < losers.size(); l++)
		{
			if (getNumberList(s,sorted).val == getNumberList(l, losers).partner)
			{
				reorderedLosers.push_back(getNumberList(l, losers));
				break ;
			}
		}
	}
	if (straggler.state != NONE)
		reorderedLosers.push_back(straggler);
	losers = reorderedLosers;
}

std::deque<Number> PmergeMe::recursiveSortDeque(std::deque<Number> c_deque)
{
	size_t pos = 1;
	std::deque<Number> winners_deque, losers_deque , sorted_deque; // we wanna get only the winners to call recursively this function

	if (DEBUG)
		showDeque(c_deque);
	if (c_deque.size() <= 2)//base case
	{
		if (c_deque.size() == 2 && c_deque[0].val > c_deque[1].val)
	        std::swap(c_deque[0], c_deque[1]);
		if (DEBUG)
			std::cout << "Recursion done, only two elements left" << std::endl;
		return c_deque;
	}
	else // we assign roles to each Number
	{
		Number straggler;
		straggler.state = NONE;
		if (c_deque.size() % 2 != 0)
		{
			straggler.val = c_deque[c_deque.size() - 1].val;
			straggler.state = LOSER;
			straggler.pos = (c_deque.size() / 2) + 1;
			c_deque.pop_back();
			if (DEBUG)
				std::cout << "Straggler is " << straggler.val << std::endl;
		}
		for (size_t i = 0; i < c_deque.size(); i+=2)// we go pair by pair comparing them
		{
			if (c_deque[i].val > c_deque[i + 1].val) //we check who wins between those two numbers
			{
				c_deque[i].state = WINNER;
				c_deque[i + 1].state = LOSER;
				c_deque[i + 1].partner = c_deque[i].val;
				winners_deque.push_back(c_deque[i]);
				losers_deque.push_back(c_deque[i + 1]);
				if (DEBUG)
					std::cout << c_deque[i].val << " is winner, " << c_deque[i + 1].val << " is loser" << std::endl;
			}
			else
			{
				c_deque[i].state = LOSER;
				c_deque[i + 1].state = WINNER;
				c_deque[i].partner = c_deque[i + 1].val;
				winners_deque.push_back(c_deque[i + 1]);
				losers_deque.push_back(c_deque[i]);
				if (DEBUG)
					std::cout << c_deque[i + 1].val << " is winner, " << c_deque[i].val << " is loser" << std::endl;
			}
			c_deque[i].pos = pos;
			c_deque[i + 1].pos = pos;
			pos++;
		}
		sorted_deque = recursiveSortDeque(winners_deque);
		assignLosersDeque(sorted_deque, losers_deque, straggler); // we reassing the losers in function of the winners which have been moved
		if (DEBUG)
			showDeque(sorted_deque);
		insertLosers(sorted_deque, losers_deque);

	}
	return sorted_deque;
}

void PmergeMe::showSelf(int which)
{
	if (which == DEQUE)
	{
		for (size_t i = 0; i < deque.size();i++)
			std::cout << deque[i].val << " ";
		std::cout << std::endl;
	}
	else if (which == LIST)
	{

		for (std::list<Number>::iterator it = list.begin(); it != list.end();it++)
			std::cout << it->val << " ";
		std::cout << std::endl;
	}
}


void PmergeMe::verifySort(int which)
{
	bool sorted = true;
	if (which == DEQUE)
	{
		for (size_t i = 0; i < deque.size() - 1;i++)
		{
			if (deque[i].val > deque[i + 1].val)
				sorted = false;
		}
	}
	else if (which == LIST)
	{
		for (size_t i = 0; i < list.size() - 1;i++)
		{
			if (getNumberList(i, list).val > getNumberList(i + 1, list).val)
				sorted = false;
		}
	}
	std::cout << (which ? "List" : "Deque") <<  (sorted ? " is sorted" : "is NOT sorted") << std::endl;
}

double PmergeMe::sortDeque()
{
	clock_t time_s = clock(); // I get the time of execution for the Deque


	deque = recursiveSortDeque(deque);
	if (DEBUG)
		showDeque(deque);
	double elapsed = ((static_cast<double>(clock() - time_s)) * 1000000.0) / (double)CLOCKS_PER_SEC;
	return elapsed;
}

Number &PmergeMe::getNumberList(size_t pos, std::list<Number> &list)
{
	std::list<Number>::iterator it = list.begin();
	while (pos--)
		it++;
	return *it;
}


void PmergeMe::insertLosers(std::list<Number> &sorted, std::list<Number> losers)
{
	sorted.push_front(getNumberList(0, losers)); // b1 always go before a1
	size_t jacob_k = 2, range_start, range_end, inserted_elements = 1;// jacobsthal step starting at two since we alr did for j(1) = 1

	while (inserted_elements < losers.size()) // we want to add all elements from losers to winners
	{
		range_start = jacobsthal(jacob_k);// j(k)
		if (range_start > losers.size())
			range_start = losers.size();

		range_end = jacobsthal(jacob_k - 1); // j(k - 1)

		while (range_start > range_end)
		{
			Number act_loser = getNumberList(range_start- 1, losers); // bcs we go from pos i but in a real deque it represents d[i - 1] to not go out of bounds

			std::list<Number>::iterator it_limit = sorted.begin();
             while (it_limit != sorted.end())
            {
                 if (it_limit->val == act_loser.partner)
                     break;
                 it_limit++;
            }
			std::list<Number>::iterator it_pos = std::lower_bound(sorted.begin(), it_limit, getNumberList(range_start - 1, losers));
			sorted.insert(it_pos, act_loser);

			range_start--;
			inserted_elements++;
		}
		jacob_k++;
	}
}

std::list<Number> PmergeMe::recursiveSortList(std::list<Number> c_list)
{
	size_t pos = 1;
	std::list<Number> winners_list, losers_list , sorted_list; // we wanna get only the winners to call recursively this function

	if (c_list.size() <= 2)//base case
	{
		if (c_list.size() == 2 && c_list.front().val > c_list.back().val)
	        std::swap( c_list.front(), c_list.back());
		return c_list;
	}
	else // we assign roles to each Number
	{
		Number straggler;
		straggler.state = NONE;
		if (c_list.size() % 2 != 0)
		{
			straggler.val = c_list.back().val;
			straggler.state = LOSER;
			straggler.pos = (c_list.size() / 2) + 1;
			c_list.pop_back();
		}
		for (size_t i = 0; i < c_list.size(); i+=2)// we go pair by pair comparing them
		{
			if (getNumberList(i, c_list).val > getNumberList(i + 1, c_list).val) //we check who wins between those two numbers
			{
				getNumberList(i, c_list).state = WINNER;
				getNumberList(i + 1, c_list).state = LOSER;
				getNumberList(i + 1, c_list).partner = getNumberList(i, c_list).val;
				winners_list.push_back(getNumberList(i, c_list));
				losers_list.push_back(getNumberList(i + 1, c_list));
			}
			else
			{
				getNumberList(i, c_list).state = LOSER;
				getNumberList(i + 1, c_list).state = WINNER;
				getNumberList(i, c_list).partner = getNumberList(i + 1, c_list).val;
				winners_list.push_back(getNumberList(i + 1, c_list));
				losers_list.push_back(getNumberList(i, c_list));
			}
			getNumberList(i, c_list).pos = pos;
			getNumberList(i + 1, c_list).pos = pos;
			pos++;
		}
		sorted_list = recursiveSortList(winners_list);
		assignLosersList(sorted_list, losers_list, straggler);
		insertLosers(sorted_list, losers_list);

	}
	return sorted_list;
}

double PmergeMe::sortList()
{
	clock_t time_s = clock(); // I get the time of execution for the Deque

	list = recursiveSortList(list);

	if (DEBUG)
		showList(list);


	double elapsed = ((static_cast<double>(clock() - time_s)) * 1000000.0) / (double)CLOCKS_PER_SEC;
	return elapsed;
}
