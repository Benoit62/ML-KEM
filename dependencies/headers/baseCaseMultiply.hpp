#ifndef BASECASEMULTIPLY_HPP
#define BASECASEMULTIPLY_HPP

// Structure pour représenter un polynôme de degré 1
struct Poly1 {
    int coeff0, coeff1;
};

Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const int q, const int gamma);

#endif
