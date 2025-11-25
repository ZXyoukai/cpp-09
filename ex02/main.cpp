/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-26 07:59:59 by dgermano          #+#    #+#             */
/*   Updated: 2025-10-26 07:59:59 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: invalid arguments." << std::endl;
        return 1;
    }
    
    try
    {
        std::string input;
        for (int i = 1; i < ac; i++)
        {
            if (i > 1)
                input += " ";
            input += av[i];
        }
        
        PmergeMe sorter;
        sorter.sort(input);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
};