/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:00:00 by dgermano          #+#    #+#             */
/*   Updated: 2025/11/24 00:00:00 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &copy) : _stack(copy._stack) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &obj)
{
    if (this != &obj)
        _stack = obj._stack;
    return *this;
}

bool RPN::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error: division by zero");
            return a / b;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

int RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token)
    {
        if (token.length() == 1 && isOperator(token[0]))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error: insufficient operands");
            
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            
            int result = calculate(a, b, token[0]);
            _stack.push(result);
        }
        else
        {
            // Verificar se é um número válido
            for (size_t i = 0; i < token.length(); i++)
            {
                if (i == 0 && (token[i] == '-' || token[i] == '+'))
                    continue;
                if (!isdigit(token[i]))
                    throw std::runtime_error("Error: invalid token");
            }
            
            std::istringstream converter(token);
            int num;
            converter >> num;
            
            if (num > 9 || num < 0)
                throw std::runtime_error("Error: numbers must be between 0 and 9");
            
            _stack.push(num);
        }
    }
    
    if (_stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    
    return _stack.top();
}
