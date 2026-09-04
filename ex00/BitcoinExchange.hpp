/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:56:46 by atabarea          #+#    #+#             */
/*   Updated: 2026/08/31 12:48:40 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		
		void	loadDatabase(const std::string &filename);
		void	processInput(const std::string &filename);
	
	private:
		std::map<std::string, float>	_priceDB;  // STL Container: map para almacenar fecha -> tasa de cambio
		
		bool	_isValidDate(const std::string &date);
		bool	_isValidValue(const std::string &value);
		float	_stringToFloat(const std::string &str);
		void	_processLine(const std::string &line);
};

#endif