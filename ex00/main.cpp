#include "BitcoinExchange.hpp"

//Move data csv to root of proyect

int	main(int ac, char **av)
{
	BitcoinExchange btc;

	if (ac != 2)
		return (ac < 2 ? std::cerr << "ERROR, too few arguments" << std::endl : std::cerr << "ERROR, too many arguments" , 1);
	if (!btc.validateFile(av[1]))
		return (1);
	if (!btc.validateFile((char *)std::string("data.csv").c_str()))
		return (1);
	btc.treatFile(std::string(av[1]));
	return (0);
}
