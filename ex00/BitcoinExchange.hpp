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
template <typename T>
class BitcoinExchange : public std::deque<T>
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		
		StoreDB(void);
	private:
		
};

#endif