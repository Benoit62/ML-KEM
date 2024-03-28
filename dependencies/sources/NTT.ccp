// main.cpp

#include <iostream>
#include <vector>
#include "ntt.hpp"

int main() {
    const int q = 256; // Modulo q

    // Exemple : coefficients du polynôme d'entrée f
    std::vector<int> f = {1, 2, 3, 4, 5, 6, 7, 8};

    // Calcul de la NTT
    computeNTT(f, q);

    // Affichage des coefficients de f̂
    std::cout << "Coefficients de f̂ : ";
    for (int coeff : f) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;

    return 0;
}
