#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN obj)
{
	this = obj;
}

RPN &RPN::operator(const RPN obj)
{
	return (*this);
}



int main(int argc, char* argv[])
{
	if (argc != 2)
		return (1);
	
}