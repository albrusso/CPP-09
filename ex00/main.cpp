/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:37 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/23 16:32:31 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sys/stat.h>
#include <string>
#include <sstream>

int isFile(std::string path)
{
	struct stat file;
	if (stat(path.c_str(), &file) != 0)
		return 0;
	return S_ISREG(file.st_mode);
}

// int isValidDate(std::string data)
// {
// 	if (data.length() != 10 || data[4] != '-' || data[7] != '-')
// 		return 0;
// 	for (int i = 0; i < data.length(); i++)
// 	{
// 		if (i == 4 || i == 7)
// 			continue;
// 		if (!std::isdigit(data[i]))
// 			return 0;
// 	}
// 	return 1;
// }

// int isValidPrice(std::string price)
// {
// 	float f;
// 	std::istringstream iss(price);
// 	if (!(iss >> f) || !iss.eof())
// 		return false;
// 	return f >= 0 && f <= 1000 && (static_cast<int>(f) == f || (price.find('.') != std::string::npos));
// }

// int isValidLine(std::string line, std::string data, std::string price)
// {
// 	int pos = line.find('|');
// 	if (pos == std::string::npos)
// 		return false;
// 	data = line.substr(0, pos);
// 	price = line.substr(pos + 1);
// 	data.erase(data.find_last_not_of(" \t"));
// 	data.erase(data.find_first_not_of(" \t"));
// 	price.erase(price.find_last_not_of(" \t"));
// 	price.erase(price.find_first_not_of(" \t"));
// 	if (!isValidDate(data) || !isValidPrice(price))
// 		return 0;
// 	return 1;
// }

int main(int ac, char **av)
{
	BitcoinExchange b(av[1]);
	if (ac != 2)
	{
		std::cout << "Try: ./btc [path_to_file]" << std::endl;
		return 1;
	}
	std::string path(av[1]);
	if (!isFile(path))
	{
		std::cout << "This, " << path << ", is not a file" << std::endl;
		return 2;
	}
	if (!b.getData())
	{
		std::cout << "Error: syntax incorrect in DB" << std::endl;
	}
	if (!b.displayData())
	{
		std::cout << "Error: could not open file." << std::endl;
	}
}