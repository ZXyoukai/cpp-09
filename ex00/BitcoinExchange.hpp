/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:51:12 by dgermano          #+#    #+#             */
/*   Updated: 2025/10/16 15:51:19 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <stdexcept>

class Date
{
    private:
        int d;
        int m;
        int y;
        float value;
    public:
        Date( const std::string & line);
        // Date( const Date & copy);
        // Date & operator = (const Date & obj);
        ~Date();
};

class BitcoinExchange
{
    private:
        std::vector<Date> dts;
    public:
        BitcoinExchange(const std::string path);
        // BitcoinExchange(const BitcoinExchange & copy);
        // BitcoinExchange & operator = (const BitcoinExchange & obj);
        ~BitcoinExchange();
};

Date::Date(const std::string  & line): y(0), d(0), m(0), value(0.0f)
{
    try
    {
        std::istringstream ss(line);
        std::string tmp;

        for (size_t i = 0; i < 4; i)
        {
            if((ss >> tmp); tmp.compare("-") )
            i++;
        }
        
        ss >> this->y;
        ss >> this->m;
        ss >> this->d;
        ss >> this->value;

        std::cout << y << m << d << value << std::endl;
        exit(0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ;
    }
    // if (y > 2025 || y < 0)
    //     std::cerr << "Error invalid year" << std::endl;
    // else if (m > 12 || m < 0)
    //     std::cerr << "Error invalid moth" << std::endl;
    // else if (d > 31 || d < 0)
    //     std::cerr << "Error invalid day" << std::endl;
    // else if (value < 0 || value > 1000)
    //     std::cerr << "Error invalid value" << std::endl;
}
Date::~Date(){};

BitcoinExchange::BitcoinExchange(const std::string path)
{
    std::fstream iFile(path);

    if(iFile.fail())
        std::cerr << "Error opening file" << std::endl;
    while (!iFile.eof())
    {
        std::string line;
        std::getline(iFile, line);
        try
        {
            Date dt(line);
            dts.push_back(dt);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
}

BitcoinExchange::~BitcoinExchange(){};
