/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:00:09 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/23 18:48:35 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
	std::cout << "RPN defaul costructor called" << std::endl;
}

RPN::RPN(std::string exp) : _exp(exp)
{
	std::cout << "RPN costructor called" << std::endl;
}

RPN::RPN(const RPN &copy) : _exp(copy._exp), _s(copy._s)
{
	std::cout << "RPN copy costructor called" << std::endl;
}

RPN &RPN::operator=(const RPN &r)
{
	if (this != &r)
	{
		_exp = r._exp;
		_s = r._s;
	}
	return *this;
}

RPN::~RPN(void)
{
	std::cout << "RPN destructor called" << std::endl;
}

int RPN::isNumber(std::string tok)
{
	if (tok.size() > 1 && tok[0] != '-')
		return 0;
	else if (tok.size() == 1 && tok[0] == '-')
			return 0;
	for (int i = 0; i < static_cast <int> (tok.size()); i++)
	{
		if (i == 0 && tok[i] == '-')
			continue;
		else if (std::isdigit(tok[i]))
			continue;
		else
			return 0;
	}
	return 1;
}

int RPN::isOperator(std::string tok)
{
	if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/')
		return 1;
	else
		throw std::invalid_argument("Invalid operator token in parsing");
}

int typeOperation(std::string op)
{
	if (op[0] == '+')
		return 1;
	if (op[0] == '-')
		return 2;
	if (op[0] == '*')
		return 3;
	if (op[0] == '/')
		return 4;
	return -1;
}

int RPN::executeOperation(std::string operation, int a, int b)
{
	int i = typeOperation(operation);
	switch (i)
	{
		case 1:
			return a + b;
		case 2:
			return a - b;
		case 3:
			return a * b;
		case 4:
			return a / b;
		default:
			throw std::runtime_error("Errore nell' esecuzione dell'operazione");
	}
}

int RPN::validate(void)
{
	std::istringstream tokens(_exp);
	std::stack <int> tmp;
	std::string tok;
	while (tokens >> tok)
	{
		if (isNumber(tok))
			tmp.push(atoi(tok.c_str()));
		else if (isOperator(tok))
		{
			if (tmp.size() < 2)
				throw std::invalid_argument("Error");
			tmp.pop();
			tmp.pop();
			tmp.push(1);
		}
		else
			throw std::invalid_argument("Error: invalid syntax");
	}
	return tmp.size() == 1;
}

int RPN::execute(void)
{
	try
	{
		validate();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::istringstream tokens(_exp);
	std::string tok;
	while (tokens >> tok)
	{
		if (isNumber(tok))
		{
			_s.push(atoi(tok.c_str()));
			// std::cout << atoi(tok.c_str()) << std::endl;
		}
		else if (isOperator(tok))
		{
			// std::cout << tok << std::endl;
			if (_s.size() < 2)
				throw std::invalid_argument("Error");
			int b = _s.top();
			_s.pop();
			// std::cout << b << std::endl;
			int a = _s.top();
			_s.pop();
			// std::cout << a << std::endl;
			int res = executeOperation(tok, a, b);
			// std::cout << res << std::endl;
			_s.push(res);
		}
		else
			throw std::invalid_argument("Error: invalid syntax");
	}
	// std::cout << _s.size() << std::endl;
	if (_s.size() != 1)
			throw std::runtime_error("Error: after operation stack has more or less 1");
	return _s.top();
}
