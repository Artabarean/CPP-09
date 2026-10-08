#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stack>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN &obj);
		RPN &operator=(const RPN &obj);
		~RPN(void);
		
		void evaluate(const std::string &expression);

		private:
			std::stack<int> _stack;
			void _applyOperation(char operation);


};