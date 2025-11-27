/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 12:56:41 by dgermano          #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) : _vectorData(copy._vectorData), _dequeData(copy._dequeData) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
    if (this != &obj)
    {
        _vectorData = obj._vectorData;
        _dequeData = obj._dequeData;
    }
    return *this;
}

std::vector<size_t> PmergeMe::generateJacobsthal(size_t n)
{
    std::vector<size_t> seq;
    size_t j0 = 1, j1 = 1;

    while (j1 < n)
    {
        seq.push_back(j1);
        size_t next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
    }

    return seq;
}

void PmergeMe::parseInput(const std::string &input)
{
    std::istringstream iss(input);
    std::string token;

    while (iss >> token)
    {
        for (size_t i = 0; i < token.length(); i++)
        {
            if (!std::isdigit(token[i]))
                throw std::runtime_error("Error: invalid input");
        }

        long num = std::atol(token.c_str());
        if (num < 0 || num > 2147483647)
            throw std::runtime_error("Error: number out of range");

        _vectorData.push_back(static_cast<int>(num));
        _dequeData.push_back(static_cast<int>(num));
    }

    if (_vectorData.empty())
        throw std::runtime_error("Error: no numbers provided");
}

template <typename T>
void PmergeMe::printContainer(const T &container, const std::string &label)
{
    std::cout << label;
    typename T::const_iterator it;
    size_t count = 0;
    for (it = container.begin(); it != container.end() && count < 5; ++it, ++count)
    {
        std::cout << *it;
        if (count < 4 && (it + 1) != container.end())
            std::cout << " ";
    }
    if (container.size() > 5)
        std::cout << " [...]";
    std::cout << std::endl;
}

template <typename T>
T PmergeMe::fordJohnsonSort(T &container)
{
    T outContainer;
    if (container.size() <= 1)
        return container;

    std::vector<typename T::value_type> small;
    std::vector<typename T::value_type> large;

    size_t i = 0;
    for (; i + 1 < container.size(); i += 2)
    {
        if (container[i] < container[i + 1])
        {
            small.push_back(container[i]);
            large.push_back(container[i + 1]);
        }
        else
        {
            small.push_back(container[i + 1]);
            large.push_back(container[i]);
        }
    }

    typename T::value_type leftover;
    bool has_leftover = false;
    std::cout << "i: " << i << " size: " << container.size() << std::endl;
    if (i < container.size())
    {
        leftover = container[i];
        has_leftover = true;
    }

    T mainChain(large.begin(), large.end());
    fordJohnsonSort(mainChain);
    printContainer(mainChain, "Main chain: ");


    std::vector<size_t> jacIdx = generateJacobsthal(small.size());

    for (size_t j = 1; j < jacIdx.size(); j++)
    {
        size_t idx = jacIdx[j];
        if (idx >= small.size())
            break;

        typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), small[idx]);
        mainChain.insert(pos, small[idx]);
    }

    for (size_t k = 0; k < small.size(); k++)
    {
        typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), small[k]);
        mainChain.insert(pos, small[k]);
    }

    if (has_leftover)
    {
        typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
        mainChain.insert(pos, leftover);
    }

    outContainer = mainChain;
    return outContainer;
}

void PmergeMe::sort(const std::string &input)
{
    clock_t start, end;
    double vectorTime;
    double dequeTime;

    parseInput(input);
    printContainer(_vectorData, "Before: ");

    start = clock();
    _vectorData = fordJohnsonSort(_vectorData);
    end = clock();
    vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    start = clock();
    _dequeData = fordJohnsonSort(_dequeData);
    end = clock();
    dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    printContainer(_vectorData, "After:  ");

    std::cout << "Time to process a range of " << _vectorData.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(5)
              << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size()
              << " elements with std::deque : " << std::fixed << std::setprecision(5)
              << dequeTime << " us" << std::endl;
}
