/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:34:27 by sacha             #+#    #+#             */
/*   Updated: 2026/03/30 14:05:51 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cctype>

// Constructeur
BitcoinExchange::BitcoinExchange() {}

// Destructeur
BitcoinExchange::~BitcoinExchange() {}

// Chargement du CSV
void BitcoinExchange::loadExchangeRatesCsv(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + filename);

	std::string line;
	if (std::getline(file, line))
	{
		if (line.find(',') == std::string::npos || line.find("date") != std::string::npos)
			;
		else
			file.seekg(0);
	}

	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		double rate;

		if (std::getline(ss, date, ',') && (ss >> rate))
		{
			while (!date.empty() && (date[0] == ' ' || date[0] == '\r'))
				date.erase(0, 1);
			while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\r'))
				date.erase(date.size() - 1, 1);

			exchangeRatesCsv.insert(std::make_pair(date, rate));
		}
	}
}

// Affichage du CSV
void BitcoinExchange::printExchangeRatesCsv() const
{
	std::multimap<std::string, double>::const_iterator it;
	for (it = exchangeRatesCsv.begin(); it != exchangeRatesCsv.end(); ++it)
	{
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

// Affichage de l’input
void BitcoinExchange::printExchangeRatesInput() const
{
	std::multimap<std::string, double>::const_iterator it;
	for (it = exchangeRatesInput.begin(); it != exchangeRatesInput.end(); ++it)
	{
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

// Chargement de l’input
void BitcoinExchange::loadInputFile(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + filename);

	std::string line;
	while (std::getline(file, line))
	{
		std::string lower = line;
		for (size_t i = 0; i < lower.size(); ++i)
			lower[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(lower[i])));
		if (lower.find("date") != std::string::npos)
			continue;

		std::istringstream ss(line);
		std::string dateStr;
		double amount;

		if (std::getline(ss, dateStr, '|'))
		{
			if (!(ss >> amount))
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue;
			}

			while (!dateStr.empty() && (dateStr[dateStr.size()-1] == ' ' || dateStr[dateStr.size()-1] == '\r'))
				dateStr.erase(dateStr.size()-1);

			if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
			{
				std::cout << "Error: bad input => " << dateStr << std::endl;
				continue;
			}

			std::string yearStr = dateStr.substr(0, 4);
			if (!isdigit(yearStr[0]) || !isdigit(yearStr[1]) || !isdigit(yearStr[2]) || !isdigit(yearStr[3]))
			{
				std::cout << "Error: bad input => " << dateStr << std::endl;
				continue;
			}

			int month = atoi(dateStr.substr(5, 2).c_str());
			int day   = atoi(dateStr.substr(8, 2).c_str());

			if (month < 1 || month > 12 || day < 1 || day > 31)
			{
				std::cout << "Error: bad input => " << dateStr << std::endl;
				continue;
			}

			if (amount < 0)
			{
				std::cout << "Error: not a positive number." << std::endl;
				continue;
			}
			if (amount > 1000)
			{
				std::cout << "Error: too large a number." << std::endl;
				continue;
			}

			exchangeRatesInput.insert(std::make_pair(dateStr, amount));
		}
	}
}
// Juste un print
void BitcoinExchange::printConvertedOutput()
{
	for (std::multimap<std::string, double>::const_iterator it = exchangeRatesInput.begin(); it != exchangeRatesInput.end(); ++it)
	{
		const std::string &date = it->first;
		double amount = it->second;

		std::multimap<std::string, double>::const_iterator csvIt = exchangeRatesCsv.upper_bound(date);
		if (csvIt == exchangeRatesCsv.begin())
		{
			std::cout << "Error: no exchange rate available for date " << date << std::endl;
			continue;
		}
		--csvIt;

		double rate = csvIt->second;
		double value = rate * amount;
		std::cout << date << " => " << amount << " * " << rate << " = " << value << std::endl;
	}
}