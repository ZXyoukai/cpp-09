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

    // Ford-Johnson algorithm para vector
    void mergeInsertSortVector(std::vector<int> &arr);
    void insertionSortVector(std::vector<int> &arr, size_t left, size_t right);
    void mergeVector(std::vector<int> &arr, size_t left, size_t mid, size_t right);

    // Ford-Johnson algorithm para deque
    void mergeInsertSortDeque(std::deque<int> &arr);
    void insertionSortDeque(std::deque<int> &arr, size_t left, size_t right);
    void mergeDeque(std::deque<int> &arr, size_t left, size_t mid, size_t right);

    // Helper functions
    void parseInput(const std::string &input);
    template<typename T>
    void printContainer(const T &container, const std::string &label);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &obj);
    ~PmergeMe();

    void sort(const std::string &input);
};

#endif
