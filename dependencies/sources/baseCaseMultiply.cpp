#include "../headers/baseCaseMultiply.hpp"
#include <iostream>
#include <cstdint>
#include <vector>


// Fonction pour calculer le produit de deux polynômes de degré 1 modulo un polynôme quadratique
Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const uint32_t q, const uint32_t gamma)
{
    Poly1 c;
    c.coeff0 = (a.coeff0 * b.coeff0 + a.coeff1 * b.coeff1 * gamma) % q;
    c.coeff1 = (a.coeff0 * b.coeff1 + a.coeff1 * b.coeff0) % q;
    return c;
}


void testBaseCaseMultiply() {
    std::vector<Poly1> polyList = {
        {0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 3}, {4, 5},
        {UINT32_MAX, 0}, {0, UINT32_MAX}, {UINT32_MAX, UINT32_MAX}
    };
    std::vector<uint32_t> qList = {3, 5, 3329, UINT32_MAX};
    std::vector<uint32_t> gammaList = {1, 2, 3, UINT32_MAX - 1};

    for (const auto& a : polyList) {
        for (const auto& b : polyList) {
            for (const auto q : qList) {
                for (const auto gamma : gammaList) {
                    Poly1 c = BaseCaseMultiply(a, b, q, gamma);
                    std::cout << "Produit de (" << a.coeff0 << " + " << a.coeff1 << "X) et (" << b.coeff0 << " + " << b.coeff1 << "X) modulo " << q << " et X^2 - " << gamma << " : "
                              << c.coeff0 << " + " << c.coeff1 << "X" << std::endl;
                }
            }
        }
    }
}