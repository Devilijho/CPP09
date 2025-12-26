#include "RPN.hpp"

int main(int ac, char **av)
{
	RPN calc;
	if (ac != 2)
		return (std::cerr<<"ERROR, Correct usage './RPN <Mathematical expression> ' ",1);
	if (!calc.verify(av[1]))
		return (1);

	calc.calculate();
	return (0);
}
