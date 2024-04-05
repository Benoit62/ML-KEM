#ifndef BASECASEMULTIPLY_HPP
#define BASECASEMULTIPLY_HPP

#include <cstdint>

// Structure pour représenter un polynôme de degré 1
struct Poly1 {
    uint16_t coeff0, coeff1;
};

Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const uint16_t q, const uint8_t gamma);  // changer q en uint_16
void testBaseCaseMultiply();

#endif
