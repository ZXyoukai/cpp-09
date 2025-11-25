/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-26 07:13:56 by dgermano          #+#    #+#             */
/*   Updated: 2025/11/24 00:00:00 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>

class RPN
{
private:
    std::stack<int> _stack;
    
    bool isOperator(char c);
    int calculate(int a, int b, char op);

public:
    RPN();
    RPN(const RPN &copy);
    RPN &operator=(const RPN &obj);
    ~RPN();
    
    int evaluate(const std::string &expression);
};

#endif