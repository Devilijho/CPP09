#include "BitcoinExchange.hpp"

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

bool BitcoinExchange::safeStoi(std::string number, int begin, int end)
{
	try
	{
		if (!(std::stoi(number) >= begin && std::stoi(number) <= end))
			return false;
	}
	catch (std::exception &e)
	{
		return false;
	}
	return true;
}

bool BitcoinExchange::validateDate(std::string date)
{
	std::string extract, rest;
	size_t pos;

	pos = date.find("-");
	if (pos == std::string::npos)
		return false;
	extract = date.substr(0, pos);
	rest = date.substr(pos + 1, date.size());
	date = rest;
	if (!safeStoi(extract, 0, 9999)) // Check if year is valid
		return false;
	pos = rest.find("-");
	if (pos == std::string::npos)
		return false;
	extract = date.substr(0, pos);
	rest = date.substr(pos + 1, date.size());
	date = rest;
	if (!safeStoi(extract, 0, 12)) // Check if month is valid
		return false;
	pos = rest.find("-");
	if (pos != std::string::npos)
		return false;
	extract = date.substr(0, date.size());
	if (!safeStoi(extract, 0, 31)) // Check if day is valid, imagine all months have 31 days :)
		return false;
	return true;
}

void BitcoinExchange::parseData(std::vector<std::pair<std::string, float> > &vector, std::string file, std::string sep)
{
	std::ifstream myfile;
	std::string line, date;
	float value;

	myfile.open(file);
	getline(myfile, line);
	while (getline(myfile, line))
	{
		size_t pos = line.find(sep);
		if (pos != std::string::npos)
		{
			date = line.substr(0, pos);
			value = stof(line.substr(pos + (sep == " | " ? 3 : 1), line.size()));
			vector.push_back(std::pair<std::string, float>(date, value));
		}
		else
			vector.push_back(std::pair<std::string, float>(std::string(""), 0));
	}
	myfile.close();
}



void BitcoinExchange::Convert(std::vector<std::pair<std::string, float> > &db, std::vector<std::pair<std::string, float> > &data)
{
	std::string date_data, date_db;
	float value_data, value_db;
	for (size_t index_data = 0; index_data < data.size(); index_data++)
	{
		date_data = data[index_data].first;
		value_data = data[index_data].second;
		if (date_data == "" || value_data == 0)
			std::cout << "ERROR, invalid input" << std::endl;
		else if (value_data < 0)
			std::cout << "ERROR, number is negative" << std::endl;
		else if (value_data > 1000)
			std::cout << "ERROR, number is too large" << std::endl;
		else if (!validateDate(date_data))
			std::cout << "ERROR, date format is wrong" << std::endl;
		else
		{
			for (size_t index_db = 0; index_db < db.size(); index_db++)	// Now we search the date hehe
			{
				date_db = db[index_db].first;
				value_db = db[index_db].second;
				std::cout << date_data << "///" << date_db << std::endl;
				if (date_db == date_data)
				{
					std::cout << date_db << " => " << value_data << " = " << value_data * value_db << std::endl;
					break;
				}
				else
				{
					if (index_db > 0)
					{
						date_db = db[index_db - 1].first;
						value_db = db[index_db - 1].second;
					}
					std::cout << date_db << " => " << value_data << " = " << value_data * value_db << std::endl;
					break;
				}
			}
			exit(1);
		}
	}
}


void BitcoinExchange::treatFile(std::string file)
{
	std::vector<std::pair<std::string, float> > db;
	std::vector<std::pair<std::string, float> > data;

	parseData(data, file, " | ");
	parseData(db, std::string("data.csv"), ",");

	Convert(db, data);
}
