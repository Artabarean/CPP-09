/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:19:34 by atabarea          #+#    #+#             */
/*   Updated: 2026/10/13 14:19:56 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN &obj)
{
	*this = obj;
}

RPN &RPN::operator=(const RPN &obj)
{
	this->_stack = obj._stack;
	return (*this);
}

RPN::~RPN(void)
{
}

void RPN::evaluate(const std::string &expression)
{
	std::stringstream input(expression);
	std::string token;

	while (!_stack.empty())
		_stack.pop();

	while (input >> token)
	{
		if (token.length() == 1 && std::isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
			_applyOperation(token[0]);
		else
			throw std::runtime_error("Error");
	}
	if (_stack.size() != 1)
	{
        throw std::runtime_error("Error");
	}
    std::cout << _stack.top() << std::endl;
}

void RPN::_applyOperation(char operation)
{
	if (_stack.size() < 2)
		throw std::runtime_error("Error");
	int right = _stack.top();
	_stack.pop();
	int left = _stack.top();
	_stack.pop();
	switch(operation)
	{
		case '+':
			_stack.push(left + right);
			break;
		case '-':
			_stack.push(left - right);
			break;
		case '/':
			if (right == 0)
				throw std::runtime_error("Error");
			_stack.push(left / right);
			break;
		case '*':
			_stack.push(left * right);
			break;
		default:
			throw std::runtime_error("Error");
	}
}
