/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:54:20 by dgermano          #+#    #+#             */
/*   Updated: 2025/10/23 15:50:18 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

static std::vector<BitcoinExchange> ReadExDatabase( void )
{
    std::fstream dbFile(DATABASE);
    std::vector<BitcoinExchange> exdbs;
    std::string line;
    
    if(dbFile.fail())
        std::cerr << "Error opening files" << std::endl;
    if (std::getline(dbFile, line) , !line.compare("date,exchange_rate"))
    {
        while (!dbFile.eof())
        {
            std::getline(dbFile, line);
            exdbs.push_back(BitcoinExchange(line, ','));
        }   
    }
    else
        std::cerr << "database is current corrupted" << std::endl;
    return exdbs;
}

static std::vector<BitcoinExchange> ReadExDatabase( const char * path )
{
    std::fstream dbFile(path);
    std::vector<BitcoinExchange> exdbs;
    std::string line = "";
    
    if(dbFile.fail())
        std::cerr << "Error opening files" << std::endl;
    if (std::getline(dbFile, line) , !line.compare("date | value"))
    {
        while (!dbFile.eof())
        {
            std::getline(dbFile, line);
            exdbs.push_back(BitcoinExchange(line, '|'));
        }   
    }
    else
        std::cerr << "database is current corrupted" << std::endl;
    return exdbs;
}

static void Exchange(const char * path)
{
    try
    {
        const std::vector<BitcoinExchange> ExDbs = ReadExDatabase();
        std::vector<BitcoinExchange> IDbs = ReadExDatabase(path);
        float rate;
        
        for (std::vector<BitcoinExchange>::iterator btx = IDbs.begin(); btx < IDbs.end(); btx++)
        {
            try
            {
                rate = (*btx).findDate(ExDbs).getRate() * (*btx).getRate();
                std::cout << *btx << " = " << rate << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cout << *btx << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Wrong: " << e.what() << '\n';
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: file not found." << std::endl;
        return 1;
    }
    
    return Exchange(av[1]), 0;
    return 0;
};