#ifndef BASECASEMULTIPLY_HPP
#define BASECASEMULTIPLY_HPP

#include <cstdint>

// Structure pour représenter un polynôme de degré 1
struct Poly1 {
    uint32_t coeff0, coeff1;
};

Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const uint32_t q, const uint32_t gamma);
void testBaseCaseMultiply();

#endif
