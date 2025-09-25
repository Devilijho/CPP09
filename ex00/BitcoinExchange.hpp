#pragma once

#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange &other);
		BitcoinExchange &operator=(BitcoinExchange &other);

		bool validateFile(char *file);
		void parseVector(std::vector<std::pair<std::string, float> > &vector, std::string file, std::string sep);
		bool validateDate(std::string date);
		void treatFile(std::string file);
};
