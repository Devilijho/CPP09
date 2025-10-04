#pragma once

#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <sstream>

struct Date
{
	int year, month, day;
};

struct Exchange
{
	Date	date;
	std::string dateStr;
	float value;
};

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange &other);
		BitcoinExchange &operator=(BitcoinExchange &other);

		bool validateFile(char *file);
		void parseData(std::vector<Exchange> &vector, std::string file, std::string sep);
		void Convert(std::vector<Exchange> &db, std::vector<Exchange> &data);
		bool safeStoi(std::string number);
		bool validateDate(Date date);
		void treatFile(std::string file);
		size_t findClosestDate(Date data, std::vector<Exchange> &db);
		void extractDate(std::vector<Exchange> &vector);

		int stringToInt(std::string str);
		float stringToFloat(std::string str);
};
