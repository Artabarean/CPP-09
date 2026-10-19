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
#include <vector>

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& obj);
		~PmergeMe(void);
		PmergeMe &operator=(const PmergeMe& obj);
		int  process_input(int argc, char* argv[]);
	private:

};