#include "BitcoinExchange.hpp"
#include <vector>

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::~BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	this->dayDB = other.dayDB;
	this->monthDB = other.monthDB;
	this->yearDB = other.yearDB;
}
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &other)
{
	if (this != &other)
	{
		this->dayDB = other.dayDB;
		this->monthDB = other.monthDB;
		this->yearDB = other.yearDB;
	}
	return *this;
}

bool BitcoinExchange::validateFile(char *file)
{
	if (access(file, F_OK))
		return (std::cout << "ERROR, file doesn't exist" << std::endl, false);
	if (access(file, R_OK))
		return (std::cout << "ERROR, file cannot be opened" << std::endl, false);
	return true;
}

bool BitcoinExchange::safeStoi(std::string number)
{
	try
	{
		stringToInt(number);
	}
	catch (std::exception &e)
	{
		return false;
	}
	return true;
}

void BitcoinExchange::extractDate(std::vector<Exchange> &vector)
{
	std::string extract, rest, dateStr;
	size_t pos;
	for (size_t index = 0; index < vector.size(); index++)
	{
		vector[index].date.day = -1;
		vector[index].date.month = -1;
		vector[index].date.year = -1;
		dateStr = vector[index].dateStr;
		pos = dateStr.find("-");
		if (pos == std::string::npos)
			continue;
		extract = dateStr.substr(0, pos);
		rest = dateStr.substr(pos + 1, dateStr.size());
		dateStr = rest;
		if (!safeStoi(extract)) // Check if year is valid
			continue;
		vector[index].date.year = stringToInt(extract);
		pos = rest.find("-");
		if (pos == std::string::npos)
			continue;
		extract = dateStr.substr(0, pos);
		rest = dateStr.substr(pos + 1, dateStr.size());
		dateStr = rest;
		if (!safeStoi(extract)) // Check if month is valid
			continue;
		vector[index].date.month = stringToInt(extract);
		pos = rest.find("-");
		if (pos != std::string::npos)
			continue;
		extract = dateStr.substr(0, dateStr.size());
		if (!safeStoi(extract)) // Check if day is valid, imagine all months have 31 days :)
			continue;
		vector[index].date.day = stringToInt(extract);
	}
}

bool BitcoinExchange::validateDate(Date date)
{
	if (date.day < 1 || date.day > 31)
		return false;
	else if (date.month < 1 || date.month > 12)
		return false;
	else if (date.year < 0 || date.year > 9999)
		return false;
	return true;
}

void BitcoinExchange::parseData(std::vector<Exchange> &vector, std::string file, std::string sep)
{
	std::ifstream myfile;
	std::string line;
	Exchange data;

	myfile.open(file.c_str());
	getline(myfile, line);
	while (getline(myfile, line))
	{
		size_t pos = line.find(sep);
		if (pos != std::string::npos)
		{
			data.dateStr = line.substr(0, pos);
			data.value = stringToFloat(line.substr(pos + (sep == " | " ? 3 : 1), line.size()));
			vector.push_back(data);
		}
		else
		{
			data.dateStr = "";
			data.value = 0;
			vector.push_back(data);
		}
	}
	myfile.close();
}



void BitcoinExchange::Convert(std::vector<Exchange> &db, std::vector<Exchange> &data)
{
	std::string dateStr_data, dateStr_db;
	float value_data, value_db;
	Date date_data;
	bool found = false;
	size_t index_db;

	for (size_t index_data = 0; index_data < data.size(); index_data++)
	{
		dateStr_data = data[index_data].dateStr;
		value_data = data[index_data].value;
		date_data = data[index_data].date;
		if (dateStr_data == "" || value_data == 0)
			std::cout << "ERROR, invalid input" << std::endl;
		else if (value_data < 0)
			std::cout << "ERROR, number is negative" << std::endl;
		else if (value_data > 1000)
			std::cout << "ERROR, number is too large" << std::endl;
		else if (!validateDate(date_data))
			std::cout << "ERROR, date format is wrong" << std::endl;
		else
		{
			found = false;
			index_db = 0;
			while (found == false && index_db < db.size())
			{
				dateStr_db = db[index_db].dateStr;
				value_db = db[index_db].value;
				if (dateStr_db == dateStr_data)
				{
					std::cout << dateStr_db << " => " << value_data << " = " << value_data * value_db << std::endl;
					found = true;
				}
				index_db++;
			}// dindt find, so search for the closest one in case found == false;
			if (!found)
			{
				index_db = findClosestDate(date_data, db);
				dateStr_db = db[index_db].dateStr;
				value_db = db[index_db].value;
				std::cout << dateStr_data << " => " << value_data << " = " << value_data * value_db << std::endl;
			}

		}
	}
}

size_t BitcoinExchange::findClosestDate(Date data, std::vector<Exchange> &db)
{
	size_t index = 0;
	int yearData = data.year , monthData = data.month, dayData = data.day;
	while (index < db.size() - 1)
	{
		if ((db[index+1].date.day >= dayData && dayData >= db[index].date.day)
			&& (db[index+1].date.month >= monthData && monthData >= db[index].date.month)
			&& (db[index+1].date.year >= yearData && yearData >= db[index].date.year))
		{
			break;
		}
		index++;
	}

	return index;
}

void BitcoinExchange::treatFile(std::string file)
{
	std::vector<Exchange> db;
	std::vector<Exchange> data;

	parseData(data, file, " | ");
	parseData(db, std::string("data.csv"), ",");

	extractDate(data);
	extractDate(db);

	Convert(db, data);
}

int BitcoinExchange::stringToInt(std::string str)
{
	std::istringstream stream(str);
	int val;
	stream >> val;
	return (val);
}

float BitcoinExchange::stringToFloat(std::string str)
{
	std::istringstream stream(str);
	float val;
	stream >> val;
	return (val);
}
