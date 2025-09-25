#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::~BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(BitcoinExchange &other){ (void)other; }
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &other){(void)other; return *this;}

bool BitcoinExchange::validateFile(char *file)
{
	if (access(file, F_OK))
		return (std::cout << "ERROR, file doesn't exist" << std::endl, false);
	if (access(file, R_OK))
		return (std::cout << "ERROR, file cannot be opened" << std::endl, false);
	return true;
}

bool BitcoinExchange::validateDate(std::string date)
{

}

void BitcoinExchange::parseVector(std::vector<std::pair<std::string, float> > &vector, std::string file, std::string sep)
{
	std::ifstream myfile;
	std::string line, date;
	float value;

	myfile.open(file);
	getline(myfile, line);
	while (getline(myfile, line))
	{
		size_t pos = line.find(sep);
		if (pos != std::string::npos) {
			date = line.substr(0, pos - 1);
			value = stol(line.substr(pos + (sep == " | " ? 3 : 1), line.size()));
			std::cout << date << ":" << value << std::endl;
			if (value >= 0)
				std::cout << "ERROR, number is negative" << std::endl;
			else if (value > 1000)
				std::cout << "ERROR, number is too large" << std::endl;
			else if (!validateDate(date))
				std::cout << "ERROR, date format is wrong" << std::endl;
			else
				vector.push_back(std::pair<std::string, float>(date, value));
		}
		else
			std::cout << "ERROR, bad input" << std::endl;
	}
	myfile.close();
}

void BitcoinExchange::treatFile(std::string file)
{
	std::vector<std::pair<std::string, float> > db;
	std::vector<std::pair<std::string, float> > data;

	parseVector(data, file, " | ");
	parseVector(db, std::string("data.csv"), ",");
}
