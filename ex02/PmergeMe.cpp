/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/11/16 11:29:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &obj)
{
	*this = obj;
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	(void)obj;
	return (*this);
}

bool PmergeMe::isNum(const char* input)
{
	int i = 0;
	while (input[i] != '\0')
	{
		if (!isdigit(input[i]))
			return (false);
		++i;
	}
	return (true);
}

bool PmergeMe::isValidNum(const char* input, int &number)
{
	char *end;
    long value;

    if (input == NULL || *input == '\0')
        return (false);
    errno = 0;
    value = std::strtol(input, &end, 10);
    if (*end != '\0' || errno == ERANGE)
        return (false);
    if (value > INT_MAX)
        return (false);
    number = static_cast<int>(value);
    return (true);
}

int PmergeMe::process_input(int argc, char* argv[])
{
	std::vector<int> unsorted;
	int number;
	for (int i = 1; i < argc; ++i)
	{
		if (!isNum(argv[i]))
		{
			std::cerr << "Error: arguments contain non numerical characters" << std::endl;
			return (-1);
		}
		if (!isValidNum(argv[i], number))
		{
			std::cerr << "Error: number too large" << std::endl;
			return (-1);
		}
		unsorted.push_back(number);
	}
	std::vector<t_pair> pairs;
	bool hasOdd = (unsorted.size() % 2 != 0);
	int odd = 0;
	if (hasOdd)
	{
		odd = unsorted.back();
		unsorted.pop_back();
	}
	std::vector<int>::iterator it;
	for (it = unsorted.begin(); it != unsorted.end(); ++it)
	{
		t_pair pair;
		int first_num = *it;
		int second_num = *(it + 1);
		if (first_num < second_num)
		{
			pair.small = first_num;
			pair.large = second_num;
		}
		else
		{
			pair.small = second_num;
			pair.large = first_num;
		}
		pairs.push_back(pair);
	}
	fordJohnson(pairs);
	std::vector<int> mainChain = buildMainChain(pairs);
	if (!pairs.empty())
		insertPendingValues(mainChain, pairs);
	if (hasOdd)
	{
		size_t position = binarySearch(mainChain, odd, mainChain.size());
		mainChain.insert(mainChain.begin() + position, odd);
	}
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator value = unsorted.begin(); value != unsorted.end(); ++value)
	{
		std::cout << *value << " ";
	}
	if (hasOdd)
		std::cout << odd << " ";
	std::cout << std::endl << "After:  ";
	for (std::vector<int>::const_iterator value = mainChain.begin(); value != mainChain.end(); ++value)
	{
		std::cout << *value << " ";
	}
	std::cout << std::endl;
	return (0);
}

void PmergeMe::fordJohnson(std::vector<t_pair>& pairs)
{
	if (pairs.size() < 2)
		return ;
	size_t middle = pairs.size() / 2;
	std::vector<t_pair> left(pairs.begin(), pairs.begin() + middle);
	std::vector<t_pair> right(pairs.begin() + middle, pairs.end());
	fordJohnson(left);
	fordJohnson(right);

	std::vector<t_pair> sorted;
	std::vector<t_pair>::const_iterator leftIt = left.begin();
	std::vector<t_pair>::const_iterator rightIt = right.begin();
	while (leftIt != left.end() && rightIt != right.end())
	{
		if (leftIt->large <= rightIt->large)
			sorted.push_back(*leftIt++);
		else
			sorted.push_back(*rightIt++);
	}
	while (leftIt != left.end())
		sorted.push_back(*leftIt++);
	while (rightIt != right.end())
		sorted.push_back(*rightIt++);
	pairs = sorted;
}

std::vector<int> PmergeMe::buildMainChain(const std::vector<t_pair>& pairs)
{
	std::vector<int> mainChain;

	std::vector<t_pair>::const_iterator position = pairs.begin();
	while (position != pairs.end())
	{
		t_pair currentPair = *position;
		if (position == pairs.begin())
			mainChain.push_back(currentPair.small);
		mainChain.push_back(currentPair.large);
		++position;
	}
	return (mainChain);
}

size_t PmergeMe::binarySearch(const std::vector<int>& values, int value, size_t end) const
{
	size_t begin = 0;
	while (begin < end)
	{
		size_t middle = begin + (end - begin) / 2;
		if (values[middle] < value)
			begin = middle + 1;
		else
			end = middle;
	}
	return (begin);
}

std::vector<size_t> PmergeMe::generateJacobsthalOrder(const std::vector<t_pair>& pairs)
{
	std::vector<size_t> order;
	size_t previous = 1;
	size_t current = 3;

	while (previous < pairs.size())
	{
		size_t end = current;
		if (end > pairs.size())
			end = pairs.size();
		for (size_t index = end; index > previous; --index)
		{
			order.push_back(index - 1);
		}
		size_t next = current + 2 * previous;
		previous = current;
		current = next;
	}
	return (order);
}

void PmergeMe::insertPendingValues(std::vector<int>& mainChain, const std::vector<t_pair>& pairs)
{
	std::vector<size_t> largePositions;
	for (size_t index = 0; index < pairs.size(); ++index)
	{
		largePositions.push_back(index + 1);
	}
	std::vector<size_t> order = generateJacobsthalOrder(pairs);
	for (std::vector<size_t>::const_iterator index = order.begin(); index != order.end(); ++index)
	{
		size_t pairIndex = *index;
		size_t position = binarySearch(mainChain, pairs[pairIndex].small, largePositions[pairIndex]);
		mainChain.insert(mainChain.begin() + position, pairs[pairIndex].small);
		for (size_t current = 0; current < largePositions.size(); ++current)
		{
			if (largePositions[current] >= position)
				++largePositions[current];
		}
	}
}
