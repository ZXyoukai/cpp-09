/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 12:56:41 by dgermano          #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <sys/time.h>

class PmergeMe
{
private:
    std::vector<int> _vectorData;
    std::deque<int> _dequeData;
    std::vector<size_t> generateJacobsthal(size_t n);
    void parseInput(const std::string &input);
    template <typename T>
    void printContainer(const T &container, const std::string &label);
    template <typename T>
    T fordJohnsonSort(T &container);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &obj);
    ~PmergeMe();
    void sort(const std::string &input);
};

#endif
