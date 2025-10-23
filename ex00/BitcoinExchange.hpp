/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:51:12 by dgermano          #+#    #+#             */
/*   Updated: 2025/10/22 12:44:45 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <stdexcept>


typedef struct t_date
{
    int day;
    int moth;
    int year;
    float rate;
    std::string excpt;
    bool valid;
} date;

std::ostream & operator <<(std::ostream & out, const date & dt);

class BitcoinExchange
{
    private:
        std::vector<date> dts;
        std::vector<date> dts_db;
    public:
        BitcoinExchange(const std::string path);
        // BitcoinExchange(const BitcoinExchange & copy);
        // BitcoinExchange & operator = (const BitcoinExchange & obj);
        ~BitcoinExchange();
};

template < typename ttype >
std::vector<ttype> split(const char * line, char _delim)
{
    std::stringstream _ss(line);
    std::vector<ttype> vec;
    std::string  item;
    ttype val;
    
    while (std::getline(_ss, item, _delim))
    {
        std::istringstream type(item);
        type >> val;
        vec.push_back(val);
    }
    return vec;
}

int check_float(const std::string & str)
{
    int pos[2];
    pos[0] = str.find('.');
    pos[1] = str.find('f');
    
    if((pos[0] != 0 && pos[0] != str.size() - 1) && (pos[1] == std::string::npos || pos[1] == str.size() - 1))
        return (1);
    return (0);

}

void validDate(date & obj,const char del)
{
    if ((obj.day > 31 || obj.day < 0 )|| (obj.moth > 12 || obj.moth < 0) || obj.year < 0)
    {
        obj.excpt =  "Invalid date format";
        return ;
    }
    if(obj.rate < 0 || obj.rate > 1000)
    {
        if(del == '|')
            obj.excpt = (obj.rate) ? "too large a number." : "not a positive number.";
        return ;
    }
}

date getDate(const std::string  & line, const char del)
{
    date _new;
    std::vector<std::string> date_rate;
    std::vector<int> data;
    
    date_rate = split<std::string>( line.c_str() , del);
    if (date_rate.size() != 2)
    {
        _new.excpt = "bad input =>";
        return (_new);
    }
    data = split<int>(date_rate[0].c_str(), '-');

    _new.day = data[2];
    _new.moth = data[1];
    _new.year = data[0];
    _new.rate = split<float>(date_rate[1].c_str(), '\n')[0];
    _new.valid = true;
    // _new.excpt = (!_new.excpt.empty()) ? "a" : _new.excpt;
    // "bad input =>"
    
    validDate(_new, del);
    return (_new);
}

BitcoinExchange::BitcoinExchange(const std::string path)
{
    std::fstream iFile(path);
    std::fstream dbFile("../cpp_09/data.csv");
    std::string line;
    
    if(iFile.fail() || dbFile.fail())
        std::cerr << "Error opening files" << std::endl;
    while (!iFile.eof())
    {
        std::getline(iFile, line);
        dts.push_back(getDate(line, '|'));
    }
    if (std::getline(dbFile, line) , !line.compare("date,exchange_rate"))
    {
        while (!dbFile.eof())
        {
            std::getline(dbFile, line);
            dts_db.push_back(getDate(line, ','));
        }
    }
    else
        std::cout << line << std::endl,
        std::cout << "database is current corrupted" << std::endl;
        
    
    // for (size_t i = 0; i < dts_db.size(); i++)
    //     std::cout << dts_db[i] << std::endl;
    // std::sort(dts_db.begin(), dts_db.end());
    for (size_t i = 0; i < dts.size(); i++)
        std::cout << dts[i] << std::endl;
    
}

BitcoinExchange::~BitcoinExchange(){};

std::ostream & operator <<(std::ostream & out, const date & dt)
{
        if (!dt.excpt.empty() && dt.valid)
        {
            out << "Error: ";
            if(dt.excpt.compare("bad input =>") == 0)
            {
                date tmp = dt;
                tmp.valid = false;
                out << dt.excpt << " " << tmp;
            }
            else
                out << dt.excpt;
            return out;
        }
        out << dt.year << ((dt.moth < 10 ) ? "-0" : "-") ;
        out << dt.moth << ((dt.day < 10 ) ? "-0" : "-");
        out << dt.day;
        if(dt.valid) out << " | " << dt.rate;
    
    return out;
}