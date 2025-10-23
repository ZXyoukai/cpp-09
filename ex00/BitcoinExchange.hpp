/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:51:12 by dgermano          #+#    #+#             */
/*   Updated: 2025/10/23 15:50:35 by dgermano         ###   ########.fr       */
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

#define DATABASE "../cpp_09/data.csv"

// std::ostream & operator <<(std::ostream & out, const date & dt);
class BitcoinExchange
{

public:
    BitcoinExchange findDate(const std::vector<BitcoinExchange> exdbs);
    typedef struct s_date
    {
        int day;
        int moth;
        int year;
    } date;
    bool valid;
    BitcoinExchange(const std::string &line, const char del);
    date getDate() const;
    float getRate() const;
    std::string getExcpt() const;
    bool operator==(const BitcoinExchange &obj)
    {
        const date dt = obj.getDate();
        return _date.year == dt.year && _date.moth == dt.moth && _date.day == dt.day;
    }

    bool operator!=(const BitcoinExchange &obj)
    {
        return !(*this == obj);
    }

    bool operator<(const BitcoinExchange &obj)
    {
        const date dt = obj.getDate();
        if (_date.year != dt.year)
            return _date.year < dt.year;
        if (_date.moth != dt.moth)
            return _date.moth < dt.moth;
        return _date.day < dt.day;
    }

    bool operator>(const BitcoinExchange &obj)
    {
        return *this < obj;
    }
    // BitcoinExchange(const BitcoinExchange & copy);
    // BitcoinExchange & operator = (const BitcoinExchange & obj);
    ~BitcoinExchange();

private:
    date _date;
    float rate;
    std::string excpt;
    void validDate(date &obj, const char del);
};

template <typename ttype>
std::vector<ttype> split(const char *line, char _delim)
{
    std::stringstream _ss(line);
    std::vector<ttype> vec;
    std::string item;
    ttype val;

    while (std::getline(_ss, item, _delim))
    {
        std::istringstream type(item);
        type >> val;
        vec.push_back(val);
    }
    return vec;
}

static int check_float(const std::string &str)
{
    int pos[2];
    pos[0] = str.find('.');
    pos[1] = str.find('f');

    if ((pos[0] != 0 && pos[0] != str.size() - 1) && (pos[1] == std::string::npos || pos[1] == str.size() - 1))
        return (1);
    return (0);
}

void BitcoinExchange::validDate(date &obj, const char del)
{
    if ((obj.day > 31 || obj.day < 0) || (obj.moth > 12 || obj.moth < 0) || obj.year < 0)
    {
        excpt = "Invalid date format";
        return;
    }
    if (rate < 0 || rate > 1000)
    {
        if (del == '|')
            excpt = (rate > 0) ? "too large a number." : "not a positive number.";
        return;
    }
}

BitcoinExchange BitcoinExchange::findDate(std::vector<BitcoinExchange> exdbs)
{
    BitcoinExchange *min = nullptr;
    BitcoinExchange *max = nullptr;

    if (excpt.empty() == 0)
        throw std::runtime_error(excpt);

    for (std::vector<BitcoinExchange>::iterator btx = exdbs.begin(); btx != exdbs.end(); ++btx)
    {
        if (*btx == *this)
            return *btx;
        if (*btx < *this && (min == nullptr || *btx > *min))
            min = &(*btx);
        if (*btx > *this && (max == nullptr || *btx < *max))
            max = &(*btx);
    }
    if (min == nullptr)
        return *max;
    if (max == nullptr)
        return *min;
    date min_date;
    date max_date;
    if (min_date.year == max_date.year)
        if (min_date.moth == max_date.moth)
            if (min_date.day == max_date.day)
                return *min;
    return ((_date.day - min_date.day) < (max_date.day - _date.day)) ? *min : *max;
    return ((_date.moth - min_date.moth) < (max_date.moth - _date.moth)) ? *min : *max;
    return ((_date.year - min_date.year) < (max_date.year - _date.year)) ? *min : *max;
}

BitcoinExchange::BitcoinExchange(const std::string &line, const char del)
{
    std::vector<std::string> date_rate;
    std::vector<int> data;

    date_rate = split<std::string>(line.c_str(), del);
    if (date_rate.size() != 2)
        excpt = "bad input => " + line;
    data = split<int>(date_rate[0].c_str(), '-');
    _date.day = data[2];
    _date.moth = data[1];
    _date.year = data[0];
    rate = split<float>(date_rate[1].c_str(), '\n')[0];
    valid = true;
    validDate(_date, del);
};

BitcoinExchange::date BitcoinExchange::getDate() const { return _date; };
float BitcoinExchange::getRate() const { return rate; };
std::string BitcoinExchange::getExcpt() const { return excpt; };

BitcoinExchange::~BitcoinExchange() {};

std::ostream &operator<<(std::ostream &out, const BitcoinExchange &btx)
{
    if (!btx.getExcpt().empty() && btx.valid)
    {
        out << "Error: ";
        if (btx.getExcpt().compare("bad input =>") == 0)
        {
            BitcoinExchange tmp = btx;
            tmp.valid = false;
            out << btx.getExcpt() << " " << tmp;
        }
        else
            out << btx.getExcpt();
        return out;
    }
    BitcoinExchange::date _date = btx.getDate();
    out << _date.year << ((_date.moth < 10) ? "-0" : "-");
    out << _date.moth << ((_date.day < 10) ? "-0" : "-");
    out << _date.day;
    if (btx.valid)
        out << " => " << btx.getRate();

    return out;
}
