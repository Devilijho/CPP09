#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange btc;

	if (ac != 2)
		return (ac < 2 ? std::cout << "ERROR, too few arguments" << std::endl : std::cout << "ERROR, too many arguments" , 1);
	if (!btc.validateFile(av[1]))
		return (1);
	if (!btc.validateFile((char *)std::string("data.csv").c_str()))
		return (1);
	btc.treatFile(std::string(av[1]));
	return (0);
}
