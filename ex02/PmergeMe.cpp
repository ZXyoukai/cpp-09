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
        // Verificar se é um número válido positivo
        for (size_t i = 0; i < token.length(); i++)
        {
            if (!isdigit(token[i]))
                throw std::runtime_error("Error: invalid input");
        }
        
        long num = atol(token.c_str());
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

// ==================== VECTOR IMPLEMENTATION ====================

void PmergeMe::insertionSortVector(std::vector<int> &arr, size_t left, size_t right)
{
    for (size_t i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        size_t j = i;
        while (j > left && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

void PmergeMe::mergeVector(std::vector<int> &arr, size_t left, size_t mid, size_t right)
{
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    size_t i = 0, j = 0, k = left;
    
    while (i < leftArr.size() && j < rightArr.size())
    {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    
    while (i < leftArr.size())
        arr[k++] = leftArr[i++];
    
    while (j < rightArr.size())
        arr[k++] = rightArr[j++];
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &arr)
{
    size_t n = arr.size();
    if (n <= 1)
        return;
    
    // Use insertion sort for small arrays
    const size_t INSERTION_THRESHOLD = 10;
    if (n <= INSERTION_THRESHOLD)
    {
        insertionSortVector(arr, 0, n - 1);
        return;
    }
    
    // Ford-Johnson: create pairs and sort them
    std::vector<std::pair<int, int> > pairs;
    size_t i;
    
    for (i = 0; i + 1 < n; i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }
    
    // Sort pairs by first element (larger element)
    for (size_t j = 1; j < pairs.size(); j++)
    {
        std::pair<int, int> key = pairs[j];
        size_t k = j;
        while (k > 0 && pairs[k - 1].first > key.first)
        {
            pairs[k] = pairs[k - 1];
            k--;
        }
        pairs[k] = key;
    }
    
    // Create main chain with larger elements
    std::vector<int> mainChain;
    std::vector<int> pend;
    
    for (size_t j = 0; j < pairs.size(); j++)
    {
        mainChain.push_back(pairs[j].first);
        pend.push_back(pairs[j].second);
    }
    
    // Add the odd element if exists
    if (i < n)
        pend.push_back(arr[i]);
    
    // Insert pending elements using binary insertion
    for (size_t j = 0; j < pend.size(); j++)
    {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
        mainChain.insert(pos, pend[j]);
    }
    
    arr = mainChain;
}

// ==================== DEQUE IMPLEMENTATION ====================

void PmergeMe::insertionSortDeque(std::deque<int> &arr, size_t left, size_t right)
{
    for (size_t i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        size_t j = i;
        while (j > left && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

void PmergeMe::mergeDeque(std::deque<int> &arr, size_t left, size_t mid, size_t right)
{
    std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    size_t i = 0, j = 0, k = left;
    
    while (i < leftArr.size() && j < rightArr.size())
    {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    
    while (i < leftArr.size())
        arr[k++] = leftArr[i++];
    
    while (j < rightArr.size())
        arr[k++] = rightArr[j++];
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &arr)
{
    size_t n = arr.size();
    if (n <= 1)
        return;
    
    // Use insertion sort for small arrays
    const size_t INSERTION_THRESHOLD = 10;
    if (n <= INSERTION_THRESHOLD)
    {
        insertionSortDeque(arr, 0, n - 1);
        return;
    }
    
    // Ford-Johnson: create pairs and sort them
    std::deque<std::pair<int, int> > pairs;
    size_t i;
    
    for (i = 0; i + 1 < n; i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }
    
    // Sort pairs by first element (larger element)
    for (size_t j = 1; j < pairs.size(); j++)
    {
        std::pair<int, int> key = pairs[j];
        size_t k = j;
        while (k > 0 && pairs[k - 1].first > key.first)
        {
            pairs[k] = pairs[k - 1];
            k--;
        }
        pairs[k] = key;
    }
    
    // Create main chain with larger elements
    std::deque<int> mainChain;
    std::deque<int> pend;
    
    for (size_t j = 0; j < pairs.size(); j++)
    {
        mainChain.push_back(pairs[j].first);
        pend.push_back(pairs[j].second);
    }
    
    // Add the odd element if exists
    if (i < n)
        pend.push_back(arr[i]);
    
    // Insert pending elements using binary insertion
    for (size_t j = 0; j < pend.size(); j++)
    {
        std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
        mainChain.insert(pos, pend[j]);
    }
    
    arr = mainChain;
}

// ==================== MAIN SORT FUNCTION ====================

void PmergeMe::sort(const std::string &input)
{
    parseInput(input);
    
    // Print before
    printContainer(_vectorData, "Before: ");
    
    // Sort with vector
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergeInsertSortVector(_vectorData);
    gettimeofday(&end, NULL);
    double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    
    // Sort with deque
    gettimeofday(&start, NULL);
    mergeInsertSortDeque(_dequeData);
    gettimeofday(&end, NULL);
    double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    
    // Print after
    printContainer(_vectorData, "After:  ");
    
    // Print timing
    std::cout << "Time to process a range of " << _vectorData.size() 
              << " elements with std::vector : " << std::fixed << std::setprecision(5) 
              << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size() 
              << " elements with std::deque : " << std::fixed << std::setprecision(5) 
              << dequeTime << " us" << std::endl;
}
