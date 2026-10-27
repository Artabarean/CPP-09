/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/10/27 11:51:49 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Error: Not enough elements" << std::endl;
		return (1);
	}
	PmergeMe array;
	if (array.process_input(argc, argv) == -1)
		return (1);
	return (0);
}