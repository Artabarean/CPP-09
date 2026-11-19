/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:28 by atabarea          #+#    #+#             */
/*   Updated: 2026/11/19 14:34:45 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <cerrno>
#include <climits>

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& obj);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe& obj);
		int  process_input(int argc, char* argv[]);
		int	 process_input_vector(int argc, char* argv[]);
		int  process_input_deque(int argc, char* argv[]);
		bool isValidNum(const char *input, int &number);
		bool isNum(const char *input);
	private:
		typedef struct s_pair
		{
			int small;
			int large;
		} t_pair;

		template <typename Container, typename PairContainer>
		int processInputForContainer(int argc, char* argv[], bool printBefore,
			bool printAfter);
		template <typename PairContainer>
		void fordJohnson(PairContainer& pairs);
		template <typename Container, typename PairContainer>
		Container buildMainChain(const PairContainer& pairs);
		template <typename Container, typename PairContainer>
		void insertPendingValues(Container& mainChain, const PairContainer& pairs);
		template <typename PairContainer>
		std::vector<size_t> generateJacobsthalOrder(const PairContainer& pairs);
		template <typename Container>
		size_t binarySearch(const Container& values, int value, size_t end) const;
};
