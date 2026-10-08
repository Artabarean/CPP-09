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

	while (input >> token)
	{
		std::cout << token << ";" << std::endl;
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
	if (_stack.empty())
		throw std::runtime_error("Error: operation performed on empty stack!");
	switch(operation)
	{
		case '+':
		{
			int num1 = _stack.top();
			_stack.pop();
			int num2 = _stack.top();
			_stack.pop();
			_stack.push(num1 + num2);
			break;
		}
		case '-':
		{
			int num1 = _stack.top();
			_stack.pop();
			int num2 = _stack.top();
			_stack.pop();
			_stack.push(num1 - num2);
			break;
		}
		case '/':
		{
			int num1 = _stack.top();
			_stack.pop();
			int num2 = _stack.top();
			_stack.pop();
			_stack.push(num1 / num2);
			break;
		}
		case '*':
		{
			int num1 = _stack.top();
			_stack.pop();
			int num2 = _stack.top();
			_stack.pop();
			_stack.push(num1 * num2);
			break;
		}
		default:
			break;	
	}
}


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

