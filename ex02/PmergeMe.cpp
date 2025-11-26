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

template<typename T>
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

// template <typename type_t>
// void mergeinsertsort(type_t &arr, size_t left, size_t right)
// {
//     const size_t INSERTION_SORT_THRESHOLD = 16;

//     if (right - left <= INSERTION_SORT_THRESHOLD)
//     {
//         for (size_t i = left + 1; i <= right; i++)
//         {
//             type_t key = arr[i];
//             size_t j = i;
//             while (j > left && arr[j - 1] > key)
//             {
//                 arr[j] = arr[j - 1];
//                 j--;
//             }
//             arr[j] = key;
//         }
//         return;
//     }

//     size_t mid = left + (right - left) / 2;
//     mergeinsertsort(arr, left, mid);
//     mergeinsertsort(arr, mid + 1, right);

//     type_t temp(right - left + 1);
//     size_t i = left, j = mid + 1, k = 0;

//     while (i <= mid && j <= right)
//     {
//         if (arr[i] <= arr[j])
//             temp[k++] = arr[i++];
//         else
//             temp[k++] = arr[j++];
//     }

//     while (i <= mid)
//         temp[k++] = arr[i++];
//     while (j <= right)
//         temp[k++] = arr[j++];

//     for (size_t m = 0; m < temp.size(); m++)
//         arr[left + m] = temp[m];
// }

void PmergeMe::sort(const std::string &input)
{
    clock_t start, end;
    double vectorTime;
    double dequeTime;

    parseInput(input);
    printContainer(_vectorData, "Before: ");
    
    start = clock();
    // mergeInsertSortVector(_vectorData);
    end = clock();
    vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
    
    start = clock();
    // mergeInsertSortDeque(_dequeData);
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
