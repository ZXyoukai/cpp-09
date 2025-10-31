/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-26 07:13:56 by dgermano          #+#    #+#             */
/*   Updated: 2025-10-26 07:13:56 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <sstream>
#include <ostream>
#include <vector>
#include <map>
#define OPERATORS "+-/*"


class RPN
{
    public:
    typedef struct t_notation
    {
        std::vector<int> _nbs;
        char expr;
    } notation;
    
    RPN(const std::string & input);
    ~RPN();
    private:
        // void calculate(std::vector<notation> & ns);
        // notation getRPN(const std::string & line);
};
std::ostream & operator<<(std::ostream & out, const RPN::notation & n);

template <typename ttype>
std::vector<ttype> split(const char *line, char _delim)
{
    std::stringstream _ss(line);
    std::vector<ttype> vec;
    std::string item;
    ttype val;
    
    while (std::getline(_ss, item, _delim))
    {
        if (item.empty()) continue;
        std::istringstream type(item);
        type >> val;
        vec.push_back(val);
    }
    return vec;
}

int _sum(int a,int b){ return a + b; };
int _sub(int a,int b){ return (b - a); };
int _mul(int a,int b){ return a * b; };
int _div(int a,int b){ return (a / b); };

void calculate(std::vector<RPN::notation> & ns)
{
    std::map<char, int (*)(int, int)> oper;
    std::size_t size;
    std::size_t i;
    RPN::notation &tmp = *ns.begin();

    oper['+'] = _sum;
    oper['-'] = _sub;
    oper['*'] = _mul;
    oper['/'] = _div;

    for (std::vector<RPN::notation>::iterator n = ns.begin(); n != ns.end(); n++)
    {
        tmp = *n;
        size = tmp._nbs.size();
        if(size == 0)
            return;

        if (size > 2)
        {
            (*(n + 1))._nbs.push_back(oper[tmp.expr](tmp._nbs[size - 2], tmp._nbs[size - 1]));
            tmp._nbs.pop_back();
            tmp._nbs.pop_back();
            if(size - 2 > 0)
            {
                i = 0;
                while (i < tmp._nbs.size())
                    (*(n + 1))._nbs.push_back(tmp._nbs[i++]);
            }
        }
        else if (size == 2)
        {
            if(size == 0)
                std::cout << "error" << std::endl;
            tmp._nbs[size - 2] = oper[tmp.expr](tmp._nbs[size - 2], tmp._nbs[size - 1]);
            // (*(n + 1))._nbs.push_back(oper[tmp.expr](tmp._nbs[size - 1], tmp._nbs[size - 2]));
            if(n + 1 != ns.end())
            {
                (*(n + 1))._nbs.push_back(tmp._nbs[size - 2]);
                tmp._nbs.pop_back();
                tmp._nbs.pop_back();
            }
            else
                tmp._nbs.pop_back();
        }
    }
    for (std::vector<RPN::notation>::iterator n = ns.begin(); n != ns.end(); n++)
        std::cout << *n << std::endl;
}
RPN::RPN(const std::string & input )
{
    std::string tmp = input;
    std::vector<notation> nts;
    std::size_t pos;
    while ((pos = tmp.find_first_of(OPERATORS)) != std::string::npos)
    {
        notation n;
        n._nbs = split<int>(tmp.substr(0, pos).c_str(), ' ');
        n.expr = tmp[pos];
        nts.push_back(n);
        tmp = tmp.substr(pos + 1);
    }
    // std::cout << "notation length = " << nts.size() << std::endl; 
    // for (size_t i = 0; i < nts.size(); i++)
    //     std::cout << nts[i] << std::endl;

    calculate(nts);
};

RPN::~RPN(){}

std::ostream & operator<<(std::ostream & out, const RPN::notation & n)
{
    for (std::vector<int>::const_iterator it = n._nbs.begin(); it != n._nbs.end(); it++)
        out << *it << ((it  + 1 == n._nbs.end()) ? "" : " ");    
    out << ((n._nbs.size() && n._nbs.size() != 1) ? " " : "");
    if(n._nbs.size() != 1)
        out << n.expr;
    return out;
}

#endif