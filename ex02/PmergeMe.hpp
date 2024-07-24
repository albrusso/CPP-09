/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:03:15 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/24 12:06:50 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <ctime>
#include <iterator>

class PmergeMe {
private:
    std::vector<int> vec;
    std::list<int> lst;

    template <typename Container>
    void mergeInsertSort(Container& container);

    template <typename Container>
    void mergeSort(Container& container, typename Container::iterator left, typename Container::iterator right);

    template <typename Container>
    void merge(Container& container, typename Container::iterator left, typename Container::iterator mid, typename Container::iterator right);

public:
    PmergeMe(const std::vector<int>& input);
    void sortAndPrint();
};

// Implementazione dell'algoritmo merge-insert sort usando template
template <typename Container>
void PmergeMe::mergeInsertSort(Container& container) {
    if (container.size() > 1) {
        mergeSort(container, container.begin(), container.end());
    }
}

template <typename Container>
void PmergeMe::mergeSort(Container& container, typename Container::iterator left, typename Container::iterator right) {
    if (std::distance(left, right) > 1) {
        typename Container::iterator mid = left;
        std::advance(mid, std::distance(left, right) / 2);

        mergeSort(container, left, mid);
        mergeSort(container, mid, right);

        merge(container, left, mid, right);
    }
}

template <typename Container>
void PmergeMe::merge(Container& container, typename Container::iterator left, typename Container::iterator mid, typename Container::iterator right) {
    Container temp(container.get_allocator()); // Usa lo stesso allocatore del contenitore originale
    typename Container::iterator itLeft = left;
    typename Container::iterator itRight = mid;

    while (itLeft != mid && itRight != right) {
        if (*itLeft <= *itRight) {
            temp.push_back(*itLeft);
            ++itLeft;
        } else {
            temp.push_back(*itRight);
            ++itRight;
        }
    }

    while (itLeft != mid) {
        temp.push_back(*itLeft);
        ++itLeft;
    }

    while (itRight != right) {
        temp.push_back(*itRight);
        ++itRight;
    }

    // Copia gli elementi ordinati dal contenitore temporaneo al contenitore originale
    std::copy(temp.begin(), temp.end(), left);
}

#endif // PMERGEME_HPP
