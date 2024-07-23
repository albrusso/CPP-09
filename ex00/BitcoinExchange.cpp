/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:11:45 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/23 16:56:38 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "BitcoinExchange default costructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string pathFile) : _pathDB("./data.csv"), _pathFile(pathFile)
{
	std::cout << "BitcoinExchange costructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _pathDB(copy._pathDB), _pathFile(copy._pathFile)
{
	*this = copy;
	std::cout << "BitcoinExchange copy costructor called" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &be)
{
	if (this != &be)
	{
		_pathDB = be._pathDB;
		_pathFile = be._pathFile;
		_tab = be._tab;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << "BitcoinExchange destructor called" << std::endl;
}

int isRealData(std::string data)
{
	int month, day, year;
	std::istringstream ss(data);
	char dash;
	if (!(ss >> year >> dash >> month >> dash >> day) || !ss.eof())
		return false;
	if (year < 2007 || year > 2024)
		return false;
	if (month < 1 || month > 12)
		return false;
	const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (isLeapYear && month == 2)
		return day >= 1 && day <= 29;
	return day >= 1 && day <= daysInMonth[month - 1];
}

int isNotFutureData(std::string data)
{
	int month = atoi(data.substr(0, 2).c_str());
	int day = atoi(data.substr(3, 2).c_str());
	int year = atoi(data.substr(6, 4).c_str());
	std::tm inputDate = {};
	inputDate.tm_year = year - 2007;
	inputDate.tm_mon = month - 1;
	inputDate.tm_mday = day;
	std::time_t inputTime = std::mktime(&inputDate);
	if (inputTime == -1)
		return false;
	std::time_t now = std::time(NULL);
	return inputTime <= now;
}

int BitcoinExchange::isValidDate(std::string data)
{
	if (!isRealData(data) || !isNotFutureData(data))
		return 0;
	return 1;
}

float BitcoinExchange::isValidPrice(std::string price)
{
	char *end;
	float f = std::strtof(price.c_str(), &end);
	if (f >= 0 && f <= 1000)
		return f;
	else if (f < 0)
		return -2;
	else if (static_cast <double> (f) > 2147483647.0)
		return -3;
	else
		return -1;
}

int BitcoinExchange::isValidLine(std::string data, std::string price)
{
	(void)price;
	if (!isValidDate(data))
		return 0;
	return 1;
}

int BitcoinExchange::getData(void)
{
	std::ifstream file(_pathDB.c_str());
	if (!file.is_open())
	{
		std::cout << "Cannot open file called " << _pathDB << std::endl;
		return 3;
	}
	std::string line;
	getline(file, line);
	while (getline(file, line))
	{
		int pos = line.find(',');
		if (pos == static_cast <int> (std::string::npos))
			return 0;
		std::string data, price;
		data = line.substr(0, pos);
		price = line.substr(pos + 1);
		if (isValidDate(data))
		{
			std::istringstream iss(price);
			float f;
			iss >> f;
			_tab[data] = f;
		}
		else
		{
			std::cout << "Bad syntax in " << _pathDB << std::endl;
			return 0;
		}
	}
	return 1;
}

int BitcoinExchange::displayData(void)
{
	std::ifstream file(_pathFile.c_str());
	if (!file.is_open())
	{
		std::cout << "Cannot open file called " << _pathFile << std::endl;
		return 1;
	}
	std::string line;
	getline(file, line);
	while (getline(file, line))
	{
		if (line.empty())
			continue;
		std::istringstream iss(line);
		std::string data, price;
		if (getline(iss, data, '|') && getline(iss, price))
		{
			data.erase(data.find_last_not_of(" \t") + 1);
			data.erase(0, data.find_first_not_of(" \t"));
			price.erase(price.find_last_not_of(" \t") + 1);
			price.erase(0, price.find_first_not_of(" \t"));
			if (isValidDate(data))
			{
				float f = isValidPrice(price);
				if (f < 0) 
				{
					if (f == -1)
					{
						std::cout << "Error: Bad input value " << price << "." << std::endl;
						continue;
					}
					if (f == -2)
					{
						std::cout << "Error: not a positive number." << std::endl;
						continue;
					}
					if (f == -3)
					{
						std::cout << "Error: too large a number." << std::endl;
						continue;
					}
				}

				std::map<std::string, float>::iterator it = _tab.lower_bound(data);
				if (it != _tab.begin() && (it == _tab.end() || it->first != data))
					it--;
				if (it != _tab.end())
					std::cout << data << " => " << f << " = " << f * it->second << std::endl;
				else
					std::cout << "Error: Date not found in map" << std::endl;
			}
			else
				std::cout << "Error: Invalid date format" << std::endl;
		}
		else
			std::cout << "Error: bad input => " << line << std::endl;
	}
	return 1;
}