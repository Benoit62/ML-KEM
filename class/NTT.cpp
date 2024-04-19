#include <cstdint>
#include <cassert>
#include <iostream>
#include <vector>
#include <array>
#include "../headers/BitArray.hpp"
#include "../headers/ByteArray.hpp"
#include "Zeta.cpp"
#include "../headers/XOF.hpp"

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Définition des constantes ML-KEM-512 
const uint16_t q = 3329;
const uint16_t n = 256;
const uint8_t k = 2;
const uint8_t eta1 = 3;
const uint8_t eta2 = 2;
const uint8_t du = 10;
const uint8_t dv = 4;

#endif // CONSTANTS_HPP



class NTT;

class Poly;

class NTTCoef {
public:
    NTTCoef(uint16_t value = 0) : value(value% q) {}

    explicit operator uint16_t() const {
        return value;
    }

    NTTCoef& operator+=(const NTTCoef& other) {
        value = (value + other.value) % q;
        return *this;
    }

    NTTCoef& operator-=(const NTTCoef& other) {
        value = (value + q - other.value) % q;
        return *this;
    }

    NTTCoef& operator*=(const NTTCoef& other) {
        value = static_cast<uint16_t>(static_cast<int32_t>(value) * static_cast<int32_t>(other.value) % q);
        return *this;
    }

    NTTCoef& operator*=(const uint16_t other) {
        value = static_cast<uint16_t>(static_cast<int32_t>(value) * static_cast<int32_t>(other) % static_cast<int32_t>(q));
        return *this;
    }

    NTTCoef& operator%=(const NTTCoef& other) {
        value = static_cast<uint16_t>(static_cast<int32_t>(value) % static_cast<int32_t>(other.value));
        return *this;
    }

    bool operator==(const NTTCoef& other) const {
        return value == other.value;
    }

    friend NTTCoef operator%(NTTCoef lhs, const NTTCoef& rhs);
    friend NTTCoef operator+(NTTCoef lhs, const NTTCoef& rhs);
    friend NTTCoef operator-(NTTCoef lhs, const NTTCoef& rhs);
    friend NTTCoef operator*(NTTCoef lhs, const NTTCoef& rhs);

    friend std::ostream& operator<<(std::ostream& os, const NTTCoef& coef);

private:
    uint16_t value;
};

NTTCoef operator+(NTTCoef lhs, const NTTCoef& rhs) {
    lhs += rhs;
    return lhs;
}

NTTCoef operator-(NTTCoef lhs, const NTTCoef& rhs) {
    lhs -= rhs;
    return lhs;
}

NTTCoef operator*(NTTCoef lhs, const NTTCoef& rhs) {
    lhs *= rhs;
    return lhs;
}

NTTCoef operator*(NTTCoef lhs, const uint16_t rhs) {
    lhs *= rhs;
    return lhs;
}

NTTCoef operator%(NTTCoef lhs, const NTTCoef& rhs) {
    lhs %= rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, const NTTCoef& coef) {
    os << coef.value;
    return os;
}


class PolyCoef {
public:
    PolyCoef(uint16_t value = 0) : value(value% q) {}

    PolyCoef& operator+=(const PolyCoef& other) {
        value = (value + other.value) % q;
        return *this;
    }

    PolyCoef& operator-=(const PolyCoef& other) {
        value = (value + q - other.value) % q;
        return *this;
    }

    PolyCoef& operator*=(const PolyCoef& other) {
        value = static_cast<uint16_t>(static_cast<int32_t>(value) * static_cast<int32_t>(other.value) % q);
        return *this;
    }

    PolyCoef& operator%=(const PolyCoef& other) {
        value = static_cast<uint16_t>(static_cast<int32_t>(value) % static_cast<int32_t>(other.value));
        return *this;
    }

    

    friend PolyCoef operator+(PolyCoef lhs, const PolyCoef& rhs);
    friend PolyCoef operator-(PolyCoef lhs, const PolyCoef& rhs);
    friend PolyCoef operator*(PolyCoef lhs, const PolyCoef& rhs);
    friend PolyCoef operator%(PolyCoef lhs, const PolyCoef& rhs);

    friend std::ostream& operator<<(std::ostream& os, const PolyCoef& coef);

private:
    uint16_t value;
};

PolyCoef operator+(PolyCoef lhs, const PolyCoef& rhs) {
    lhs += rhs;
    return lhs;
}

PolyCoef operator-(PolyCoef lhs, const PolyCoef& rhs) {
    lhs -= rhs;
    return lhs;
}

PolyCoef operator*(PolyCoef lhs, const PolyCoef& rhs) {
    lhs *= rhs;
    return lhs;
}

PolyCoef operator%(PolyCoef lhs, const PolyCoef& rhs) {
    lhs %= rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, const PolyCoef& coef) {
    os << coef.value;
    return os;
}


class NTT {
public:

    NTT() {};

    template <std::size_t n>
    NTT(const Poly& f) {
        std::array<uint16_t, n> f_hat = f;

         uint16_t k = 1;

         for (uint16_t len = 128; len >= 2; len /= 2) {
             for (uint16_t start = 0; start < N; start += 2 * len) {

                 k++;

                 for (uint16_t j = start; j < start + len; j++) {
                     int32_t t = static_cast<int32_t>(Zeta.getZeta(k)) * static_cast<int32_t>(f_hat[j + len]);
                     f_hat[j + len] = static_cast<uint16_t>((static_cast<int32_t>(f_hat[j]) - t % q + q) % q);
                     f_hat[j] = static_cast<uint16_t>((static_cast<int32_t>(f_hat[j]) + t % q) % q);
                 }
             }
         }

        coefficients = f_hat;
    }

    NTT(const std::array<NTTCoef, n>& input) {
        std::array<uint16_t, n> f_hat = {};
        for (size_t i = 0; i < n; i++) {
            f_hat[i] = static_cast<uint16_t>(input[i]);
        }

        uint16_t k = 1;
        for (uint16_t len = 128; len >= 2; len /= 2) {
            for (uint16_t start = 0; start < n; start += 2 * len) {
                k++;
                for (uint16_t j = start; j < start + len; j++) {
                    int32_t t = static_cast<int32_t>(zetaList[k]) * static_cast<int32_t>(f_hat[j + len]);
                    f_hat[j + len] = static_cast<uint16_t>((static_cast<int32_t>(f_hat[j]) - t % q + q) % q);
                    f_hat[j] = static_cast<uint16_t>((static_cast<int32_t>(f_hat[j]) + t % q) % q);
                }
            }
        }

        //coefficients = f_hat;
        for (size_t i = 0; i < n; i++) {
            coefficients[i] = f_hat[i];
        }
    }

    NTTCoef get(std::size_t i) const {
        return coefficients[i];
    }

    void set(std::size_t i, const NTTCoef& coef) {
        coefficients[i] = coef;
    }

    static NTT SampleNTT(const XOF B) {
        NTT a;
        uint32_t i = 0;
        uint32_t j = 0;
        uint32_t d1, d2;

         while (j < 256) {
             d1 = B.digest[i] + 256 * (B.digest[i + 1] % 16);
             d2 = static_cast<int>(floor(B.digest[i + 1] / 16.0)) + 16 * B.digest[i + 2];

             if (d1 < q) {
                 a.set(j, d1);
                 j++;
             }

             if (d2 < q && j < 256) {
                 a.set(j, d2);
                 j++;
             }
             i += 3;
         }

        return a;
    }

    // Get tab coefficients
    std::array<NTTCoef, n> getCoef()
    {
        return coefficients;
    }

    // Surcharge = pour NTT
    NTT& operator=(const NTT& other)
    {
        coefficients = other.coefficients;
        return *this;
    }

    NTT& operator*(const NTT& other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] * other.coefficients[i];
        }
        return *this;
    }

    NTT& operator+(const NTT& other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] + other.coefficients[i];
        }
        return *this;
    }

    static void testNTT() {
        // Générer un tableau de valeurs aléatoires
        std::array<NTTCoef, n> input;
        for (auto& x : input) {
            x = NTTCoef(rand() % q);
        }
        // Créer l'objet NTT à partir du tableau
        NTT ntt(input);
        // Vérifier que la transformation est correcte
        for (size_t i = 0; i < n; i++) {
            assert(ntt.get(i) == input[i]);
        }
        std::cout << "Test NTT réussi !" << std::endl;
    }

private:
    std::array<NTTCoef, n> coefficients;

    NTT MultiplyNTTs(const NTT& f, const NTT& g)
    {
        NTT h;
        NTTCoef c0;
        NTTCoef c1;

        for (uint16_t i = 0; i < n / 2; i++)
        {
            NTTCoef a0 = f.get(2 * i);
            NTTCoef a1 = f.get(2 * i + 1);
            NTTCoef b0 = g.get(2 * i);
            NTTCoef b1 = g.get(2 * i + 1);
            uint16_t gamma = gammaList[i];
            BaseCaseMultiply(a0, a1, b0, b1, c0, c1, gamma);

            h.set(2 * i, c0);
            h.set(2 * i + 1, c1);
        }
        return h;
    }

    void BaseCaseMultiply(const NTTCoef a0, const NTTCoef a1, const NTTCoef b0, const NTTCoef b1, NTTCoef& c0, NTTCoef& c1, const uint16_t gamma)
    {
        c0 = a0 * b0 + a1 * b1 * gamma;
        c1 = a0 * b1 + a1 * b0;
    }
};


class Poly {
public:

    Poly() {};

    template <std::size_t n>
    Poly(const NTT& f_hat) {
        std::array<PolyCoef, n> f = f_hat;

         uint16_t k = 127;

         for (uint16_t len = 2; len <= 128; len <<= 1) {
             for (uint16_t start = 0; start < 256; start += 2 * len) {

                 k--;

                 for (uint16_t j = start; j < start + len; j++) {
                    //équivalent au pseudo-code
                    //pour éviter les dépassement en mémoire
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

    NTTCoef get(std::size_t i) const {
        return coefficients[i];
    }

    void set(std::size_t i, const NTTCoef& coef) {
        coefficients[i] = coef;
    }

    static Poly SamplePolyCBD_eta(const ByteArray& B, uint32_t eta, uint32_t q) {
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
    std::array<NTTCoef, n> getCoef()
    {
        return coefficients;
    }

    // Surcharge = pour Poly
    Poly& operator=(const Poly& other)
    {
        coefficients = other.coefficients;
        return *this;
    }

    Poly& operator+(const Poly& other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] + other.coefficients[i];
        }
        return *this;
    }

private:

    std::array<NTTCoef, n> coefficients;
};
