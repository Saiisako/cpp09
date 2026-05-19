/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:34:23 by skock             #+#    #+#             */
/*   Updated: 2026/05/19 13:50:09 by skock            ###   ########.fr       */
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
		std::vector<Pair>	vec;
		std::deque<Pair>	deq;
		std::vector<int>	resultVec;
		std::deque<int>		resultDeq;
	public:
		PmergeMe();
		PmergeMe(char **av);
		~PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		//	Printing
		void	printVec(const std::vector<Pair> &vec);
		void	printDeq(const std::deque<Pair> &deq);
		void	PrintTimeCodeVec();
		void	PrintTimeCodeDeq();
		//	Algorithm
		void	sortVec();
		void	sortDeq();
		void	insertPendVec(std::vector<int> &big,
							  std::vector<int> &small,
							  std::vector<Pair> &sortedVec);
		void	insertPendDeq(std::deque<int> &big,
							  std::deque<int> &small,
							  std::deque<Pair> &sortedDeq);

};