/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:21:52 by skock             #+#    #+#             */
/*   Updated: 2026/04/03 12:29:08 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) { (void)other;}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		this->stack = other.stack;
	return (*this);
}

void RPN::calculate(const std::string &expression)
{
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
				throw std::runtime_error("Not enough operands for: " + token);

			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();

			if (token == "+")      stack.push(a + b);
			else if (token == "-") stack.push(a - b);
			else if (token == "*") stack.push(a * b);
			else
			{
				if (b == 0) throw std::runtime_error("Division by zero");
				stack.push(a / b);
			}
		}
		else
		{
			if (token.size() != 1 || !std::isdigit(static_cast<unsigned char>(token[0])))
				throw std::runtime_error("Invalid token: " + token);
			stack.push(token[0] - '0');
		}
	}

	if (stack.size() != 1)
		throw std::runtime_error("Invalid RPN expression");

	std::cout << stack.top() << std::endl;
}

