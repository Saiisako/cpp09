/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:34:23 by skock             #+#    #+#             */
/*   Updated: 2026/04/09 14:34:23 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>


struct Pair
{
	int small;
	int big;

	Pair(int s, int b) : small(s), big(b) {}
};


class PmergeMe
{
	private:
		std::vector<Pair> vec;
		std::deque<Pair> deq;

	public:
		PmergeMe(char **av);
		~PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);

		void printVec(const std::vector<Pair> &vec);
		void printDeq(const std::deque<Pair> &deq);
		
		void sortVec();
		std::vector<Pair>& mergeSort(std::vector<Pair> &v);
		// void sortDeq(std::deque<Pair> &d);
};