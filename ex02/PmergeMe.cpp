/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/10/27 12:24:59 by atabarea         ###   ########.fr       */
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
	// for (size_t i = 0; i < unsorted.size(); ++i)
	// {
	// 	std::cout << unsorted[i] << std::endl;
	// }
	std::vector<t_pair> pairs;
	std::vector<int>::iterator it;
	int first_num;
	int second_num;
	for (it = unsorted.begin(); it != unsorted.end(); it++)
	{
		first_num = *it;
		if (it + 1 != unsorted.end())
		{
			t_pair pair;
			++it;
			second_num = *it;
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
	}
	fordJohnson(pairs);
	std::vector<int>mainChain = buildMainChain(pairs);
	return (0);
}

void PmergeMe::fordJohnson(std::vector<t_pair>& pairs)
{
	if (pairs.size() < 2)
		return ;
	std::vector<t_pair> winners;
	std::vector<t_pair> losers;
	std::vector<t_pair>::iterator it = pairs.begin();
	while (it != pairs.end())
	{
		t_pair first = *it++;
		if (it == pairs.end())
		{
			losers.push_back(first);
			break ;
		}
		t_pair second = *it++;
		if (first.large < second.large)
		{
			winners.push_back(second);
			losers.push_back(first);
		}
		else
		{
			winners.push_back(first);
			losers.push_back(second);
		}
	}
	fordJohnson(winners);
	std::vector<t_pair> chain;
	chain.push_back(losers.front());
	chain.insert(chain.end(), winners.begin(), winners.end());
	for (size_t i = 1; i < losers.size(); ++i)
	{
		t_pair value = losers[i];
		std::vector<t_pair>::iterator position = chain.begin();
		while (position != chain.end() && position->large < value.large)
			++position;
		chain.insert(position, value);
	}
	pairs = chain;
}

std::vector<int> PmergeMe::buildMainChain(std::vector<t_pair>& pairs)
{
	std::vector<int> mainChain;

	std::vector<t_pair>::iterator position = pairs.begin();
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