#include "../headers/Poly.hpp"

    Poly::Poly() {};

    template <std::size_t n>
    Poly::Poly(const NTT& f_hat) {
        // Pourquoi ne pas avoir rempli l'attibut coefficients avec les coeffs de f_hat ?
        std::array<PolyCoef, n> f = f_hat;

        uint16_t k = 127;

        for (uint16_t len = 2; len <= 128; len <<= 1) {
            for (uint16_t start = 0; start < 256; start += 2 * len) {

                k--;

                for (uint16_t j = start; j < start + len; j++) {
                    //équivalent au pseudo-code
                    //pour éviter les dépassement en mémoire
                    // Bonne utilisation de NTTCoef et de ses surcharges !!!!
                    NTTCoef t = f[j];
                    NTTCoef tmp1 = (f[j] + f[j + len]) % q;
                    f[j] = (tmp1 + q) % q;
                    NTTCoef tmp2 = (zetaList[k] * (f[j + len] - t)) % q;
                    f[j + len] = (tmp2 + q) % q;
                }
            }
        }

        for (NTTCoef& x : f) {
            x = (x * 3303) % q;
        }
        coefficients = f;
    }

    NTTCoef Poly::get(std::size_t i) const {
        return coefficients[i];
    }

    void Poly::set(std::size_t i, const NTTCoef& coef) {
        coefficients[i] = coef;
    }

    // Utilité de q en tant que paramètre ? Il est censé être une constante globale
    Poly Poly::SamplePolyCBD_eta(const ByteArray& B, uint32_t eta, uint32_t q) {
        ByteArray BB = B;
        BitArray b = BitArray::bytesToBits(BB);
        Poly f;

        for (int i = 0; i < 256; i++) {
            uint32_t x = 0;
            uint32_t y = 0;

            for (int j = 0; j < eta; j++) {
                x += b.getIndex(2 * i * eta + j);
                y += b.getIndex(2 * i * eta + eta + j);
            }

            f.set(i, (x - y + q) % q);
        }
        return f;
    }

    // Get tab coefficients
    std::array<NTTCoef, n> Poly::getCoef()
    {
        return coefficients;
    }

    // Surcharge = pour Poly
    Poly& Poly::operator=(const Poly& other)
    {
        coefficients = other.coefficients;
        return *this;
    }

    Poly& Poly::operator+(const Poly& other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            // Pourquoi ne pas utiliser get(i) pour other ?
            this->coefficients[i] = coefficients[i] + other.coefficients[i];
        }
        return *this;
    }
