/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:21 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/24 12:07:19 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main(void) {
    // Genera una sequenza di 3000 numeri interi positivi casuali
    std::vector<int> input;
    const int num_elements = 100;
    srand(static_cast<unsigned>(time(0))); // Inizializza il generatore di numeri casuali

    for (int i = 0; i < num_elements; ++i) {
        input.push_back(rand() % 10000 + 1); // Genera numeri casuali tra 1 e 10000
    }

    PmergeMe sorter(input);
    sorter.sortAndPrint();

    return 0;
}
