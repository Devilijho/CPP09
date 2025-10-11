#include "RPN.hpp"

int main(int ac, char **av)
{
	RPN calc;
	if (ac != 2)
		return (std::cout<<"ERROR, Correct usage './RPN <Mathematical expression> ' ",1);
	if (!calc.verify(av[1]))
		return (std::cout<<"ERROR, Input not valid ",1);

	calc.build();
	return (0);
}
