/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:34:29 by sacha             #+#    #+#             */
/*   Updated: 2026/03/30 11:21:38 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<std::string, double> exchangeRatesCsv;
		std::multimap<std::string, double> exchangeRatesInput;

	public:
		BitcoinExchange();
		~BitcoinExchange();

		void loadExchangeRatesCsv(const std::string& filename);
		void loadInputFile(const std::string& filename);
		void printExchangeRatesCsv() const;
		void printExchangeRatesInput() const;
		void printConvertedOutput();
};