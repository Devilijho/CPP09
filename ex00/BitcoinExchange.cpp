#include "BitcoinExchange.hpp"
#include <algorithm>


BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::~BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	(void)other;
}
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &other)
{
	(void)other;
	return *this;
}

bool BitcoinExchange::validateFile(char *file)
{
	if (access(file, F_OK))
		return (std::cerr << "ERROR, '"<< file <<  "' doesn't exist" << std::endl, false);
	if (access(file, R_OK))
		return (std::cerr << "ERROR, '"<< file <<  "' cannot be opened" << std::endl, false);
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

bool BitcoinExchange::onlyDigits(std::string str)
{
	if (str.size() < 10) // YYYY-MM-DD
		return false;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (i != 4 && i != 7 && (str[i] < '0' || str[i] > '9'))
			return false;
		if (i == 4 || i == 7)
		{
			if (str[i] != '-')
				return false;
		}
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
		if (onlyDigits(dateStr) && (!safeStoi(extract) || extract.size() != 4)) // Check if year is valid
			continue;
		vector[index].date.year = stringToInt(extract);
		pos = rest.find("-");
		if (pos == std::string::npos)
			continue;
		extract = dateStr.substr(0, pos);
		rest = dateStr.substr(pos + 1, dateStr.size());
		dateStr = rest;
		if (onlyDigits(dateStr) &&(!safeStoi(extract) || extract.size() != 2)) // Check if month is valid
			continue;
		vector[index].date.month = stringToInt(extract);
		pos = rest.find("-");
		if (pos != std::string::npos)
			continue;
		extract = dateStr.substr(0, dateStr.size());
		if (onlyDigits(dateStr) && (!safeStoi(extract) || extract.size() != 2)) // Check if day is valid, imagine all months have 31 days :)
			continue;
		vector[index].date.day = stringToInt(extract);
	}
}

bool BitcoinExchange::validateDate(Date date)
{
    if (date.year < 0 || date.month < 1 || date.month > 12)
        return false;

    int maxDays;

    if (date.month == 2)
    {
        bool isLeap = (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0));
        maxDays = isLeap ? 29 : 28;
    }
    else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
        maxDays = 30;
    else
        maxDays = 31;

    if (date.day < 1 || date.day > maxDays)
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

long BitcoinExchange::getDateValue(Date& d)
{
	return (d.year * 10000) + (d.month * 100) + (d.day);
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
		if (dateStr_data == "" || value_data == ERRORCASE)
			std::cout << "ERROR, invalid input" << std::endl;
		else if (value_data < 0)
			std::cout << "ERROR, number is negative" << std::endl;
		else if (value_data > 1000)
			std::cout << "ERROR, number is too large" << std::endl;
		else if (!validateDate(date_data) || !onlyDigits(dateStr_data))
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
	long inputVal = getDateValue(data);

    if (inputVal < getDateValue(db[0].date))
        return 0;

    for (size_t i = 0; i < db.size(); i++)
    {
        long dbVal = getDateValue(db[i].date);

        if (dbVal > inputVal)
        {
            return (i > 0) ? i - 1 : 0;
        }
    }
    return db.size() - 1;
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
	if (!stream.eof())
		return ERRORCASE;
	return (val);
}
