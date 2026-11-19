/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/11/19 14:35:14 by atabarea         ###   ########.fr       */
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
	return (processInputForContainer<std::vector<int>, std::vector<t_pair> >(argc,
			argv, true, true));
}

int PmergeMe::process_input_vector(int argc, char* argv[])
{
	return (processInputForContainer<std::vector<int>, std::vector<t_pair> >(argc,
			argv, false, false));
}

int PmergeMe::process_input_deque(int argc, char* argv[])
{
	return (processInputForContainer<std::deque<int>, std::deque<t_pair> >(argc,
			argv, false, false));
}

template <typename Container, typename PairContainer>
int PmergeMe::processInputForContainer(int argc, char* argv[], bool printBefore,
	bool printAfter)
{
	Container unsorted;
	Container originalValues;
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
		originalValues.push_back(number);
	}
	PairContainer pairs;
	bool hasOdd = (unsorted.size() % 2 != 0);
	int odd = 0;
	if (hasOdd)
	{
		odd = unsorted.back();
		unsorted.pop_back();
	}
	for (typename Container::iterator it = unsorted.begin(); it != unsorted.end(); ++it)
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
		if (it + 1 != unsorted.end())
			it = it + 1;
	}
	fordJohnson<PairContainer>(pairs);
	Container mainChain = buildMainChain<Container, PairContainer>(pairs);
	if (!pairs.empty())
		insertPendingValues<Container, PairContainer>(mainChain, pairs);
	if (hasOdd)
	{
		size_t position = binarySearch<Container>(mainChain, odd, mainChain.size());
		mainChain.insert(mainChain.begin() + position, odd);
	}
	if (printBefore)
	{
		std::cout << "Before: ";
		for (typename Container::const_iterator value = originalValues.begin(); value != originalValues.end(); ++value)
		{
			std::cout << *value << " ";
		}
		std::cout << std::endl;
	}
	if (printAfter)
	{
		std::cout << "After: ";
		for (typename Container::const_iterator value = mainChain.begin(); value != mainChain.end(); ++value)
		{
			std::cout << *value << " ";
		}
		std::cout << std::endl;
	}
	return (0);
}

template <typename PairContainer>
void PmergeMe::fordJohnson(PairContainer& pairs)
{
	if (pairs.size() < 2)
		return ;
	size_t middle = pairs.size() / 2;
	PairContainer left(pairs.begin(), pairs.begin() + middle);
	PairContainer right(pairs.begin() + middle, pairs.end());
	fordJohnson<PairContainer>(left);
	fordJohnson<PairContainer>(right);
	PairContainer sorted;
	typename PairContainer::const_iterator leftIt = left.begin();
	typename PairContainer::const_iterator rightIt = right.begin();
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

template <typename Container, typename PairContainer>
Container PmergeMe::buildMainChain(const PairContainer& pairs)
{
	Container mainChain;

	for (typename PairContainer::const_iterator position = pairs.begin(); position != pairs.end(); ++position)
	{
		t_pair currentPair = *position;
		if (position == pairs.begin())
			mainChain.push_back(currentPair.small);
		mainChain.push_back(currentPair.large);
	}
	return (mainChain);
}

template <typename Container>
size_t PmergeMe::binarySearch(const Container& values, int value, size_t end) const
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

template <typename PairContainer>
std::vector<size_t> PmergeMe::generateJacobsthalOrder(const PairContainer& pairs)
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

template <typename Container, typename PairContainer>
void PmergeMe::insertPendingValues(Container& mainChain, const PairContainer& pairs)
{
	std::vector<size_t> largePositions;
	for (size_t index = 0; index < pairs.size(); ++index)
	{
		largePositions.push_back(index + 1);
	}
	std::vector<size_t> order = generateJacobsthalOrder<PairContainer>(pairs);
	for (std::vector<size_t>::const_iterator index = order.begin(); index != order.end(); ++index)
	{
		size_t pairIndex = *index;
		size_t position = binarySearch<Container>(mainChain, pairs[pairIndex].small, largePositions[pairIndex]);
		mainChain.insert(mainChain.begin() + position, pairs[pairIndex].small);
		for (size_t current = 0; current < largePositions.size(); ++current)
		{
			if (largePositions[current] >= position)
				++largePositions[current];
		}
	}
}
