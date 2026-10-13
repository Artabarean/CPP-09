/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:39 by atabarea          #+#    #+#             */
/*   Updated: 2026/10/13 14:20:21 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try
    {
        RPN calculator;
        calculator.evaluate(argv[1]);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return (1);
    }
    return (0);
	
}
