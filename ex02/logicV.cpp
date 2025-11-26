#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cmath>

class PmergeMe {
public:
    // Função principal para ordenar
    template <typename T>
    void fordJohnsonSort(T& container) {
        if (container.size() <= 1)
            return;

        // 1. Criar pares
        std::vector<typename T::value_type> small;
        std::vector<typename T::value_type> large;

        size_t i = 0;
        for (; i + 1 < container.size(); i += 2) {
            if (container[i] < container[i + 1]) {
                small.push_back(container[i]);
                large.push_back(container[i + 1]);
            } else {
                small.push_back(container[i + 1]);
                large.push_back(container[i]);
            }
        }

        // Se sobrar um elemento (n ímpar)
        typename T::value_type leftover;
        bool has_leftover = false;
        if (i < container.size()) {
            leftover = container[i];
            has_leftover = true;
        }

        // 2. Ordenar os "large" recursivamente (main chain)
        T mainChain(large.begin(), large.end());
        fordJohnsonSort(mainChain);

        // 3. Inserir os "small" usando a sequência de Jacobsthal
        std::vector<size_t> jacIdx = generateJacobsthal(small.size());

        for (size_t j = 0; j < jacIdx.size(); j++) {
            size_t idx = jacIdx[j];
            if (idx >= small.size()) break;

            // Inserção binária (binary insertion)
            typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), small[idx]);
            mainChain.insert(*pos, small[idx]);
        }

        // Inserir leftover se houver
        if (has_leftover) {
            typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
            mainChain.insert(*pos, leftover);
        }

        // Voltar para o container original
        std::copy(mainChain.begin(), mainChain.end(), container.begin());
    }

private:
    // Sequência de Jacobsthal
    std::vector<size_t> generateJacobsthal(size_t n) {
        std::vector<size_t> seq;
        size_t j0 = 0, j1 = 1;

        while (j1 < n) {
            seq.push_back(j1);
            size_t next = j1 + 2 * j0;
            j0 = j1;
            j1 = next;
        }

        return seq;
    }
};
