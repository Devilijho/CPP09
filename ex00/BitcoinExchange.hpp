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
		void parseData(std::vector<std::pair<std::string, float> > &vector, std::string file, std::string sep);
		void Convert(std::vector<std::pair<std::string, float> > &db, std::vector<std::pair<std::string, float> > &data);
		bool safeStoi(std::string number, int begin, int end);
		bool validateDate(std::string date);
		void treatFile(std::string file);
};
