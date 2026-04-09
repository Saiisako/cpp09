/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:28:24 by sacha             #+#    #+#             */
/*   Updated: 2026/04/09 13:57:53 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <string>
#include <cctype>
#include <climits>
#include <cstdlib>

int parseInput(char **av)
{
	int count = 0;

	for (int i = 1; av[i]; ++i)
	{
		std::string arg(av[i]);

		if (arg.empty())
			return 1;

		for (size_t j = 0; j < arg.size(); ++j)
		{
			if (!std::isdigit(static_cast<unsigned char>(arg[j])))
				return 1;
		}
		char *endptr;
		long value = std::strtol(arg.c_str(), &endptr, 10);

		if (*endptr != '\0')
			return 1;
		if (value < INT_MIN || value > INT_MAX)
			return 1;

		count++;
	}
    return 0;
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: Parsing !" << std::endl;
		return 1;
	}
	if (parseInput(av))
	{
		std::cerr << "Error: Parsing !" << std::endl;
		return 1;
	}
	PmergeMe pmerge(av);
	
	pmerge.sortVec();
	// sortDeq();
	return 0;
}