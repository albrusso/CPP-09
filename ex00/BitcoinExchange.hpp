/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/23 16:51:09 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <ctime>

class BitcoinExchange
{
	private:
		std::string _pathDB;
		std::string _pathFile;
		std::map <std::string, float> _tab;
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::string pathFile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &be);
		~BitcoinExchange(void);

	float isValidPrice(std::string price);
	int isValidDate(std::string data);
	int isValidLine(std::string data, std::string price);
	int getData(void);
	int displayData(void);
};

#endif
