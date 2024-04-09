#include "../headers/baseCaseMultiply.hpp"
#include <iostream>
#include <cstdint>
#include <vector>


// Calcule le produit de deux polynômes de degré 1 modulo un polynôme quadratique
Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const uint16_t q, const uint8_t gamma)  //  enlever q
{
    uint64_t coeff0 = (static_cast<uint64_t>(a.coeff0) * b.coeff0 + static_cast<uint64_t>(a.coeff1) * b.coeff1 * static_cast<uint64_t>(gamma)) % static_cast<uint64_t>(q);
    uint64_t coeff1 = (static_cast<uint64_t>(a.coeff0) * b.coeff1 + static_cast<uint64_t>(a.coeff1) * b.coeff0) % static_cast<uint64_t>(q);
    Poly1 c {static_cast<uint16_t>(coeff0), static_cast<uint16_t>(coeff1)};

    return c;
}


void testBaseCaseMultiply() {
    std::vector<Poly1> polyList = {
        {0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 3}, {4, 5},
        {UINT16_MAX, 0}, {0, UINT16_MAX}, {UINT16_MAX, UINT16_MAX}
    };
    std::vector<uint16_t> qList = {3, 5, 7, 3329, UINT16_MAX};
    std::vector<uint8_t> gammaList = {1, 2, 3, UINT8_MAX};

    for (const auto& a : polyList) {
        for (const auto& b : polyList) {
            for (const auto q : qList) {
                for (const auto gamma : gammaList) {
                    Poly1 c = BaseCaseMultiply(a, b, q, gamma);
                    std::cout << "(" << a.coeff0 << " + " << a.coeff1 << "X) * (" << b.coeff0 << " + " << b.coeff1 << "X) % " << q << " et X^2 - " << gamma << " : "
                              << c.coeff0 << " + " << c.coeff1 << "X" << std::endl;
                }
            }
        }
    }
}