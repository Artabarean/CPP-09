/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:28 by atabarea          #+#    #+#             */
/*   Updated: 2026/10/15 12:33:28 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
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
		bool isValidNum(const char *input, int &number);
		bool isNum(const char *input);
	private:
		typedef struct s_pair
		{
			int small;
			int large;
		} t_pair;
		
		void fordJohnson(std::vector<t_pair>& pairs);

};
