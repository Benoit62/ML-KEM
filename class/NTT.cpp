#include <cstdint>
#include <iostream>
#include <vector>
#include <array>

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Définition des constantes ML-KEM-512 
const uint16_t q = 3329;
const uint16_t n = 256;
const uint16_t zeta = 17;  // pas sûr pour uint16_t, à enlever et calculer dans la class Zeta
const uint8_t k = 2;
const uint8_t eta1 = 3;
const uint8_t eta2 = 2;
const uint8_t du = 10;
const uint8_t dv = 4;

#endif // CONSTANTS_HPP

class NTTCoef {
public:
    NTTCoef(uint32_t value = 0) : value(value% q) {}

    NTTCoef& operator+=(const NTTCoef& other) {
        value = (value + other.value) % q;
        return *this;
    }

    NTTCoef& operator-=(const NTTCoef& other) {
        value = (value + q - other.value) % q;
        return *this;
    }

    NTTCoef& operator*=(const NTTCoef& other) {
        value = static_cast<uint32_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other.value) % q);
        return *this;
    }

    friend NTTCoef operator+(NTTCoef lhs, const NTTCoef& rhs);
    friend NTTCoef operator-(NTTCoef lhs, const NTTCoef& rhs);
    friend NTTCoef operator*(NTTCoef lhs, const NTTCoef& rhs);

    friend std::ostream& operator<<(std::ostream& os, const NTTCoef& coef);

private:
    uint32_t value;
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

std::ostream& operator<<(std::ostream& os, const NTTCoef& coef) {
    os << coef.value;
    return os;
}


class PolyCoef {
public:
    PolyCoef(uint32_t value = 0) : value(value% q) {}

    PolyCoef& operator+=(const PolyCoef& other) {
        value = (value + other.value) % q;
        return *this;
    }

    PolyCoef& operator-=(const PolyCoef& other) {
        value = (value + q - other.value) % q;
        return *this;
    }

    PolyCoef& operator*=(const PolyCoef& other) {
        value = static_cast<uint32_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other.value) % q);
        return *this;
    }

    friend PolyCoef operator+(PolyCoef lhs, const PolyCoef& rhs);
    friend PolyCoef operator-(PolyCoef lhs, const PolyCoef& rhs);
    friend PolyCoef operator*(PolyCoef lhs, const PolyCoef& rhs);

    friend std::ostream& operator<<(std::ostream& os, const PolyCoef& coef);

private:
    uint32_t value;
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

std::ostream& operator<<(std::ostream& os, const PolyCoef& coef) {
    os << coef.value;
    return os;
}


class Poly {
public:

    Poly() {}

    template <std::size_t n>
    Poly(const std::array<NTTCoef, n>& f_hat, const std::array<uint16_t, 128>& zetas) {
        std::array<PolyCoef, n> f = f_hat;

        uint32_t k = 127;

        for (uint32_t len = 2; len <= 128; len <<= 1) {
            for (uint32_t start = 0; start < 256; start += 2 * len) {
                ll zeta = mod_pow(static_cast<ll>(zetas[k]), 1, q);
                k--;

                for (uint32_t j = start; j < start + len; j++) {
                    NTTCoef t = f[j];
                    NTTCoef tmp1 = (f[j] + f[j + len]) % q;
                    f[j] = (tmp1 + q) % q;
                    NTTCoef tmp2 = (zeta * (f[j + len] - t)) % q;
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

    static Poly SamplePolyCBD_eta(const std::vector<uint8_t>& B, uint32_t eta, uint32_t q) {
        Poly result;
        // Implémentation de la fonction SamplePolyCBD_eta
        return result;
    }


private:

    std::array<NTTCoef, n> coefficients;
    const std::size_t maxSize = n;
};