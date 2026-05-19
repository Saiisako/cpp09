/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:34:21 by skock             #+#    #+#             */
/*   Updated: 2026/05/19 13:19:13 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ─── Constructeurs / Destructeur ───────────────────────────────────────────

PmergeMe::PmergeMe() {}

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

PmergeMe::PmergeMe(char **av)
{
	for (int i = 1; av[i]; ++i)
	{
		int a = std::atoi(av[i]);
		if (a < 0)
			throw std::invalid_argument("Negative number");

		if (av[i + 1])
		{
			int b = std::atoi(av[++i]);
			if (b < 0)
				throw std::invalid_argument("Negative number");
			if (a < b)
				std::swap(a, b);
			vec.push_back(Pair(b, a));
			deq.push_back(Pair(b, a));
		}
		else
		{
			vec.push_back(Pair(-42, a));
			deq.push_back(Pair(-42, a));
		}
	}
}


// ─── Print ─────────────────────────────────────────────────────────────────

void PmergeMe::printVec(const std::vector<Pair> &v)
{
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i].big << " ";
	std::cout << std::endl;
}

void PmergeMe::printDeq(const std::deque<Pair> &d)
{
	for (size_t i = 0; i < d.size(); ++i)
		std::cout << d[i].big << " ";
	std::cout << std::endl;
}

// ─── Jacobsthal ────────────────────────────────────────────────────────────

static std::vector<size_t> getJacobsthal(size_t n)
{
	std::vector<size_t> jac;
	jac.push_back(1);
	jac.push_back(3);
	while (jac.back() < n)
	{
		size_t s = jac.size();
		jac.push_back(jac[s - 1] + 2 * jac[s - 2]);
	}
	return jac;
}

// ─── MergeSort vector ──────────────────────────────────────────────────────

static std::vector<Pair>& mergeSort(std::vector<Pair> &v)
{
	if (v.size() <= 1)
		return v;

	size_t mid = v.size() / 2;
	std::vector<Pair> left(v.begin(), v.begin() + mid);
	std::vector<Pair> right(v.begin() + mid, v.end());

	mergeSort(left);
	mergeSort(right);

	size_t i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i].big <= right[j].big)
			v[k++] = left[i++];
		else
			v[k++] = right[j++];
	}
	while (i < left.size()) v[k++] = left[i++];
	while (j < right.size()) v[k++] = right[j++];

	return v;
}

// ─── MergeSort deque ───────────────────────────────────────────────────────

static std::deque<Pair>& mergeSort(std::deque<Pair> &d)
{
	if (d.size() <= 1)
		return d;

	size_t mid = d.size() / 2;
	std::deque<Pair> left(d.begin(), d.begin() + mid);
	std::deque<Pair> right(d.begin() + mid, d.end());

	mergeSort(left);
	mergeSort(right);

	size_t i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i].big <= right[j].big)
			d[k++] = left[i++];
		else
			d[k++] = right[j++];
	}
	while (i < left.size()) d[k++] = left[i++];
	while (j < right.size()) d[k++] = right[j++];

	return d;
}

// ─── Insertion Jacobsthal vector ───────────────────────────────────────────

void PmergeMe::insertPendVec(std::vector<int> &big, std::vector<int> &small, std::vector<Pair> &sortedVec)
{
	if (small.empty()) return;

	big.insert(big.begin(), small[0]);
	if (small.size() == 1) return;

	std::vector<size_t> jac = getJacobsthal(small.size());

	size_t prev = 1;
	for (size_t k = 1; k < jac.size(); ++k)
	{
		size_t curr = std::min(jac[k], small.size());

		for (int i = (int)curr - 1; i >= (int)prev; --i)
		{
			std::vector<int>::iterator bound =
				std::find(big.begin(), big.end(), sortedVec[i].big);

			std::vector<int>::iterator pos =
				std::lower_bound(big.begin(), bound + 1, small[i]);

			big.insert(pos, small[i]);
		}

		prev = curr;
		if (prev >= small.size()) break;
	}
}

// ─── Insertion Jacobsthal deque ────────────────────────────────────────────

void PmergeMe::insertPendDeq(std::deque<int> &big, std::deque<int> &small, std::deque<Pair> &sortedDeq)
{
	if (small.empty()) return;

	big.insert(big.begin(), small[0]);
	if (small.size() == 1) return;

	std::vector<size_t> jac = getJacobsthal(small.size());

	size_t prev = 1;
	for (size_t k = 1; k < jac.size(); ++k)
	{
		size_t curr = std::min(jac[k], small.size());

		for (int i = (int)curr - 1; i >= (int)prev; --i)
		{
			std::deque<int>::iterator bound =
				std::find(big.begin(), big.end(), sortedDeq[i].big);

			std::deque<int>::iterator pos =
				std::lower_bound(big.begin(), bound + 1, small[i]);

			big.insert(pos, small[i]);
		}

		prev = curr;
		if (prev >= small.size()) break;
	}
}

// ─── Sort vector ───────────────────────────────────────────────────────────

void PmergeMe::sortVec()
{
	int orphan = -1;
	if (!vec.empty() && vec.back().big == -42)
	{
		orphan = vec.back().small;
		vec.pop_back();
	}

	mergeSort(vec);

	std::vector<int> big;
	std::vector<int> small;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i].big == -42)
			continue;
		big.push_back(vec[i].big);
		small.push_back(vec[i].small);
	}

	insertPendVec(big, small, vec);

	if (orphan != -1)
	{
		std::vector<int>::iterator pos =
			std::lower_bound(big.begin(), big.end(), orphan);
		big.insert(pos, orphan);
	}

	resultVec = big;
}

// ─── Sort deque ────────────────────────────────────────────────────────────

void PmergeMe::sortDeq()
{
	int orphan = -1;
	if (!deq.empty() && deq.back().big == -42)
	{
		orphan = deq.back().small;
		deq.pop_back();
	}

	mergeSort(deq);

	std::deque<int> big;
	std::deque<int> small;
	for (size_t i = 0; i < deq.size(); ++i)
	{
		if (deq[i].big == -42)
			continue;
		big.push_back(deq[i].big);
		small.push_back(deq[i].small);
	}

	insertPendDeq(big, small, deq);

	if (orphan != -1)
	{
		std::deque<int>::iterator pos =
			std::lower_bound(big.begin(), big.end(), orphan);
		big.insert(pos, orphan);
	}

	resultDeq = big;
}

// ─── Timers ────────────────────────────────────────────────────────────────

void PmergeMe::PrintTimeCodeVec()
{
	clock_t start = clock();
	sortVec();
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << vec.size() * 2
			  << " elements with std::vector : " << time << " us" << std::endl;
	for (size_t i = 0; i < resultVec.size(); ++i)
	{
		if (resultVec[i] == -42)
			continue;
		std::cout << resultVec[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::PrintTimeCodeDeq()
{
	clock_t start = clock();
	sortDeq();
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << deq.size() * 2
	<< " elements with std::deque : " << time << " us" << std::endl;
	for (size_t i = 0; i < resultDeq.size(); ++i)
	{
		if (resultDeq[i] == -42)
			continue;
		std::cout << resultDeq[i] << " ";
	}
	std::cout << std::endl;
}