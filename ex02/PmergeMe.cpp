/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:03:31 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/24 12:03:32 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Costruttore della classe
PmergeMe::PmergeMe(const std::vector<int>& input) : vec(input), lst(input.begin(), input.end()) {}

// Funzione per ordinare e stampare i risultati
void PmergeMe::sortAndPrint() {
    std::cout << "Sequenza non ordinata: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    clock_t start, end;

    // Ordinamento usando il primo contenitore (vector)
    start = clock();
    mergeInsertSort(vec);
    end = clock();
    double vectorSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << "Sequenza ordinata (vector): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Tempo impiegato usando vector: " << vectorSortTime << " secondi" << std::endl;

    // Ordinamento usando il secondo contenitore (list)
    start = clock();
    mergeInsertSort(lst);
    end = clock();
    double listSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << "Sequenza ordinata (list): ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Tempo impiegato usando list: " << listSortTime << " secondi" << std::endl;
}
