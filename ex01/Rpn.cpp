#include "Rpn.hpp"

Rpn ::Rpn ()
{
}

/*--------------------------------------------------------*/
Rpn::Rpn (const Rpn &ref)
{
	this->operator=(ref);
}

/*--------------------------------------------------------*/
Rpn::~Rpn ()
{
}

/*--------------------------------------------------------*/
Rpn & Rpn::operator = (const Rpn &ref)
{
		(void)ref;
	return (*this);
}

int Rpn::result(int n1, int n2, char operators)
{
	switch (operators)
	{
		case '+':
			return (n1 + n2);
		case '-':
			return (n2 - n1);
		case '*':
			return (n1 * n2);
		case '/':
		{
			if (n2 == 0)
				throw std::invalid_argument("Floating Point Exception Dividing on Zero\n");
			return (n2 / n1);
		}
	}
	return (0);
}


void    Rpn::readInput(std::string input)
{
	std::string operators = "+/*-";
	size_t op, num;
	op = num = 0;
	for (size_t i = 0; i < input.length() ; i++)
	{
		if (isdigit(input[i]))
		{
			num++;
			this->_numbers.push(input[i] - '0');
		}
		else if (operators.find(input[i]) != std::string::npos)
		{
			op++;
			int n1 = _numbers.top();
			_numbers.pop();
			_numbers.top() = result(n1, _numbers.top(), input[i]);
		}

		else if (isspace(input[i]))
			continue;
		else
			throw std::invalid_argument("Invalid Input\n");
	}
	if ((op + 1) != num)
		throw std::invalid_argument("Number of operatorsrators less or greater than numbers\n");
	std::cout << _numbers.top() << "\n";
}
