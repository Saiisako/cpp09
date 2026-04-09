	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2026/04/03 12:34:21 by skock             #+#    #+#             */
	/*   Updated: 2026/04/09 14:02:16 by skock            ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "PmergeMe.hpp"

	// Constructeur
	void PmergeMe::printVec(const std::vector<Pair> &vec)
	{
		std::cout << "Vec" << std::endl;
		std::cout << "[ ";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << "{" << vec[i].big << ":" << vec[i].small << "}";
			if (i + 1 < vec.size())
				std::cout << " | ";
		}
		std::cout << " ]" << std::endl;
	}

	void PmergeMe::printDeq(const std::deque<Pair> &deq)
	{
		std::cout << "Deq" << std::endl;
		std::cout << "[ ";
		for (size_t i = 0; i < deq.size(); ++i)
		{
			std::cout << "{" << deq[i].big << ":" << deq[i].small << "}";
			if (i + 1 < deq.size())
				std::cout << " | ";
		}
		std::cout << " ]" << std::endl;
	}

	PmergeMe::PmergeMe(char **av)
	{
		for (int i = 1; av[i]; ++i)
		{
			int a = std::atoi(av[i]);

			if (av[i + 1])
			{
				int b = std::atoi(av[++i]);
				if (a < b) std::swap(a, b);
				vec.push_back(Pair(a, b));
				deq.push_back(Pair(a, b));
			}
			else
			{
				vec.push_back(Pair(-42, a));
				deq.push_back(Pair(-42, a));
			}
			printVec(vec);
			printDeq(deq);
		}
	}

	// Destructeur
	PmergeMe::~PmergeMe() {}

	PmergeMe::PmergeMe(const PmergeMe &other)
	{
		this->vec = other.vec;
		this->deq = other.deq;
	}

	PmergeMe &PmergeMe::operator=(const PmergeMe &other)
	{
		if (this != &other)
		{
			this->vec = other.vec;
			this->deq = other.deq;
		}
		return (*this);
	}

	void PmergeMe::sortVec()
	{
		if (vec.size() <= 1)
			return;
		
	}