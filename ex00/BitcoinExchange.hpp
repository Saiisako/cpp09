/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacha <sacha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:34:29 by sacha             #+#    #+#             */
/*   Updated: 2026/03/26 12:31:02 by sacha            ###   ########.fr       */
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
        std::map<std::string, double> exchangeRates;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        void loadExchangeRates(const std::string& filename);
};
