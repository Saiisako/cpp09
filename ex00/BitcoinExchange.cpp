/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:34:27 by sacha             #+#    #+#             */
/*   Updated: 2026/03/30 11:21:25 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		double rate;

		if (std::getline(ss, date, ',') && (ss >> rate))
		{
			exchangeRatesCsv[date] = rate;
		}
	}
}

// Affichage du CSV
void BitcoinExchange::printExchangeRatesCsv() const
{
	std::map<std::string, double>::const_iterator it;
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
		std::istringstream ss(line);
		std::string date;
		double rate;

		if (std::getline(ss, date, '|') && (ss >> rate))
		{
			exchangeRatesInput.insert(std::make_pair(date, rate));
		}
	}
}