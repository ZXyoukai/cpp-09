/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 12:56:41 by dgermano          #+#    #+#             */
/*   Updated: 2025-10-31 12:56:41 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <vector>

class PmergeMe
{
private:
public:
    PmergeMe(const std::string &input);
    ~PmergeMe();
};

template <typename ttype>
std::stack<ttype> split(const char *line, char _delim)
{
    std::stringstream _ss(line);
    std::stack<ttype> vec;
    std::string item;
    ttype val;

    while (std::getline(_ss, item, _delim))
    {
        if (item.empty())
            continue;
        std::istringstream type(item);
        type >> val;
        vec.push(val);
    }
    return vec;
}

PmergeMe::PmergeMe(const std::string &input)
{
    const std::stack<int> stk = split<int>(input.c_str(), ' ');
    std::stack<int> tmp = stk;

    while (!tmp.empty())
        std::cout << tmp.top() << " ", tmp.pop();
    std::cout << std::endl;
}

PmergeMe::~PmergeMe() {};
