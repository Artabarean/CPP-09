/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/11/19 12:54:12 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <iomanip>
#include "PmergeMe.hpp"

static double nowUs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 100000.0 + tv.tv_usec);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Error: Not enough elements" << std::endl;
		return (1);
	}
	PmergeMe array;
	double vectorTimeUs = 0.0;
	double dequeTimeUs = 0.0;
	double startUs = nowUs();
	int vectorReturn = array.process_input(argc, argv);
	vectorTimeUs = nowUs() - startUs;
	if (vectorReturn == -1)
		return (1);
	startUs = nowUs();
	int dequeReturn = array.process_input_deque(argc, argv);
	dequeTimeUs = nowUs() - startUs;
	if (dequeReturn == -1)
		return (1);
	double vectorTimeSec = vectorTimeUs / 100000.0;
	double dequeTimeSec = dequeTimeUs / 100000.0;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << (argc - 1)
          << " elements with std::vector : " << vectorTimeSec << " us" << std::endl;
	std::cout << "Time to process a range of " << (argc - 1)
          << " elements with std::deque  : " << dequeTimeSec << " us" << std::endl;
	return (0);
}