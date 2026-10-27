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
	std::vector<int> biggest_in_pair;
	std::vector<int> smallest_in_pair;
	std::vector<int>::iterator it;
	int first_compared;
	int second_compared;
	for (it = unsorted.begin(); it != unsorted.end(); it++)
	{
		first_compared = *it;
		if (it + 1 != unsorted.end())
		{
			++it;
			second_compared = *it;
			if (first_compared > second_compared)
			{
				biggest_in_pair.push_back(first_compared);
				smallest_in_pair.push_back(second_compared);
			}
			else
			{
				biggest_in_pair.push_back(second_compared);
				smallest_in_pair.push_back(first_compared);
			}
		}
		else
			smallest_in_pair.push_back(first_compared);
	}
	// std::cout << "biggest_in_pair:" << std::endl;
	// for (size_t i = 0; i < biggest_in_pair.size(); ++i)
	// {
	// 	std::cout << biggest_in_pair[i] << std::endl;
	// }
	// std::cout << "smallest_in_pair:" << std::endl;
	// for (size_t i = 0; i < smallest_in_pair.size(); ++i)
	// {
	// 	std::cout << smallest_in_pair[i] << std::endl;
	// }
	return (0);
}