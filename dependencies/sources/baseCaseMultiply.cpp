#include "baseCaseMultiply.hpp"


// Fonction pour calculer le produit de deux polynômes de degré 1 modulo un polynôme quadratique
Poly1 BaseCaseMultiply(const Poly1 a, const Poly1 b, const int q, const int gamma)
{
    Poly1 c;
    c.coeff0 = (a.coeff0 * b.coeff0 + a.coeff1 * b.coeff1 * gamma) % q;
    c.coeff1 = (a.coeff0 * b.coeff1 + a.coeff1 * b.coeff0) % q;
    return c;
}
