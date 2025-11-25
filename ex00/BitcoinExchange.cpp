/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-26 06:58:48 by dgermano          #+#    #+#             */
/*   Updated: 2025-10-26 06:58:48 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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

std::string BitcoinExchange::dateToString() const
{
    std::stringstream ss;
    ss << _date.year << "-";
    if (_date.moth < 10) ss << "0";
    ss << _date.moth << "-";
    if (_date.day < 10) ss << "0";
    ss << _date.day;
    return ss.str();
}

BitcoinExchange BitcoinExchange::findDate(const std::map<std::string, float> &exdbs)
{
    if (excpt.empty() == 0)
        throw std::runtime_error(excpt);

    std::string searchDate = dateToString();
    
    // Procura a data exata ou a mais próxima anterior
    std::map<std::string, float>::const_iterator it = exdbs.lower_bound(searchDate);
    
    // Se encontrou a data exata
    if (it != exdbs.end() && it->first == searchDate)
    {
        BitcoinExchange result(*this);
        result.rate = it->second;
        return result;
    }
    
    // Se não encontrou e está no início, usa a primeira data
    if (it == exdbs.begin())
    {
        BitcoinExchange result(*this);
        result.rate = it->second;
        return result;
    }
    
    // Caso contrário, usa a data anterior
    --it;
    BitcoinExchange result(*this);
    result.rate = it->second;
    return result;
}

BitcoinExchange::BitcoinExchange(const std::string &line, const char del)
{
    std::vector<std::string> date_rate;
    std::vector<int> data;

    date_rate = split<std::string>(line.c_str(), del);
    if (date_rate.size() != 2)
    {
        excpt = "bad input => " + line;
        return ;
    }
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
BitcoinExchange::BitcoinExchange(const BitcoinExchange & copy)
{
    _date = copy.getDate();
    rate = copy.getRate();
    excpt = copy.getExcpt();
    valid = copy.valid;
}
BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange & obj)
{
    if (this != &obj)
    {
        _date = obj.getDate();
        rate = obj.getRate();
        excpt = obj.getExcpt();
        valid = obj.valid;
    }
    return *this;
}

bool BitcoinExchange::operator==(const BitcoinExchange &obj) const
{
    const date dt = obj.getDate();
    return _date.year == dt.year && _date.moth == dt.moth && _date.day == dt.day;
}

bool BitcoinExchange::operator!=(const BitcoinExchange &obj) const
{
    return !(*this == obj);
}

bool BitcoinExchange::operator<(const BitcoinExchange &obj) const
{
    const date dt = obj.getDate();
    if (_date.year != dt.year)
        return _date.year < dt.year;
    if (_date.moth != dt.moth)
        return _date.moth < dt.moth;
    return _date.day < dt.day;
}

bool BitcoinExchange::operator>(const BitcoinExchange &obj) const
{
    return obj < *this;
}

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
