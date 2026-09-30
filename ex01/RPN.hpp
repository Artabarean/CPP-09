#pragma once

#include <iostream>
#include <string>
#include <stack>

template <typename T>
class RPN : public std::stack<T>
{
	public:
		RPN(void);
		RPN(char* argv[]);
		RPN(const RPN obj);
		RPN &operator=(const RPN obj);
		~RPN(void);
};