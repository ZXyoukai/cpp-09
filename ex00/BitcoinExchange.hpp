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

#define DATABASE "./data.csv"

class BitcoinExchange;
std::ostream &operator<<(std::ostream &out, const BitcoinExchange &btx);
class BitcoinExchange
{

public:
    typedef struct s_date
    {
        int day;
        int moth;
        int year;
    } date;
    date getDate() const;
    std::string getExcpt() const;
    bool valid;
    float getRate() const;
    bool operator==(const BitcoinExchange &obj) const;
    bool operator!=(const BitcoinExchange &obj) const;
    bool operator<(const BitcoinExchange &obj) const;
    bool operator>(const BitcoinExchange &obj) const;
    BitcoinExchange(const BitcoinExchange & copy);
    BitcoinExchange(const std::string &line, const char del);
    BitcoinExchange & operator = (const BitcoinExchange & obj);
    BitcoinExchange findDate(const std::map<std::string, float> &exdbs);
    std::string dateToString() const;
    ~BitcoinExchange();

private:
    date _date;
    std::string excpt;
    float rate;
    void validDate(date &obj, const char del);
};