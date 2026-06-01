/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:34:29 by sacha             #+#    #+#             */
/*   Updated: 2026/06/01 11:23:33 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cstdlib>

class BitcoinExchange
{
	private:
		std::multimap<std::string, double> exchangeRatesCsv;
		std::multimap<std::string, double> exchangeRatesInput;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		
		//P PARSING
		bool isValidDate(const std::string &dateStr);
		
		void loadExchangeRatesCsv(const std::string& filename);
		void loadInputFile(const std::string& filename);
		void printConvertedOutput();
		// PRINTING
		void printExchangeRatesCsv() const;
		void printExchangeRatesInput() const;
	};