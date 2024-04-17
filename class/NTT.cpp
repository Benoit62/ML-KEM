#include <cstdint>
#include <iostream>
#include <vector>
#include <array>
#include "BitArray.hpp"
#include "XOF.cpp"

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

    NTTCoef &operator*=(const uint16_t other){
        value = static_cast<uint16_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other) % static_cast<int64_t>(q));
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

NTTCoef operator*(NTTCoef lhs, const uint16_t rhs) {
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


//template <typename PolyCoef>
class NTT {
public:

    NTT(){};

    template <std::size_t n>
    /*NTT(const Poly& f, const std::array<uint16_t, 128>& zetas) {
        std::array<uint32_t, n> f_hat = f;

    //     uint32_t k = 1;

    //     for (uint32_t len = 128; len >= 2; len /= 2) {
    //         for (uint32_t start = 0; start < N; start += 2 * len) {
    //             uint32_t zeta = mod_pow(17, BitRev7(k), q);
    //             zetas[k] = zeta;
    //             k++;

    //             for (uint32_t j = start; j < start + len; j++) {
    //                 int64_t t = static_cast<int64_t>(zeta) * static_cast<int64_t>(f_hat[j + len]);
    //                 f_hat[j + len] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) - t % q + q) % q);
    //                 f_hat[j] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) + t % q) % q);
    //             }
    //         }
    //     }

        coefficients = f_hat;
    }*/

    NTTCoef get(std::size_t i) const {
        return coefficients[i];
    }

    void set(std::size_t i, const NTTCoef& coef) {
        coefficients[i] = coef;
    }

    /*static NTT SampleNTT(const XOF B) {
        std::vector<uint32_t> a;
        uint32_t i = 0;
        uint32_t j = 0;
        uint32_t d1, d2;

    //     while (j < 256) {
    //         d1 = B.digest[i] + 256 * (B.digest[i + 1] % 16);
    //         d2 = static_cast<int>(floor(B.digest[i + 1] / 16.0)) + 16 * B.digest[i + 2];

    //         if (d1 < q) {
    //             a.push_back(d1);
    //             j++;
    //         }

    //         if (d2 < q && j < 256) {
    //             a.push_back(d2);
    //             j++;
    //         }
    //         i += 3;
    //     }

        return a;
    }*/

    // Get tab coefficients
    std::array<NTTCoef, n> getCoef()
    {
        return coefficients;
    }

    // Surcharge = pour Poly
    NTT &operator=(const NTT &other)
    {
        coefficients = other.coefficients;
        maxSize = other.maxSize;
        return *this;
    }

    NTT &operator*(const NTT &other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] * other.coefficients[i];
        }
        return *this;
    }

    NTT &operator+(const NTT &other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] + other.coefficients[i];
        }
        return *this;
    }

private:
    std::array<NTTCoef, n> coefficients;
    // const std::size_t maxSize = n;

    NTT MultiplyNTTs(const NTT &f, const NTT &g)
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


//template <typename CoefType>
class Poly {
public:

    Poly(){};

    template <std::size_t n>
    /*Poly(const NTT& f_hat, const std::array<uint16_t, 128>& zetas) {
        std::array<PolyCoef, n> f = f_hat;

    //     uint32_t k = 127;

    //     for (uint32_t len = 2; len <= 128; len <<= 1) {
    //         for (uint32_t start = 0; start < 256; start += 2 * len) {
    //             ll zeta = mod_pow(static_cast<ll>(zetas[k]), 1, q);
    //             k--;

    //             for (uint32_t j = start; j < start + len; j++) {
    //                 NTTCoef t = f[j];
    //                 NTTCoef tmp1 = (f[j] + f[j + len]) % q;
    //                 f[j] = (tmp1 + q) % q;
    //                 NTTCoef tmp2 = (zeta * (f[j + len] - t)) % q;
    //                 f[j + len] = (tmp2 + q) % q;
    //             }
    //         }
    //     }

        for (NTTCoef& x : f) {
            x = (x * 3303) % q;
        }
        coefficients = f;
    }*/

    NTTCoef get(std::size_t i) const {
        return coefficients[i];
    }

    void set(std::size_t i, const NTTCoef& coef) {
        coefficients[i] = coef;
    }

    static Poly SamplePolyCBD_eta(const Poly& B, uint32_t eta, uint32_t q) {
        BitArray b = 0;     /// bytesToBits(B);
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
    Poly &operator=(const Poly &other)
    {
        coefficients = other.coefficients;
        maxSize = other.maxSize;
        return *this;
    }

    Poly &operator*(const Poly &other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] * other.coefficients[i];
        }
        return *this;
    }

    Poly &operator+(const Poly &other)
    {
        for (int i = 0; i < coefficients.size(); i++)
        {
            this->coefficients[i] = coefficients[i] + other.coefficients[i];
        }
        return *this;
    }

private:

    std::array<NTTCoef, n> coefficients;
    std::size_t maxSize = n;
};

class PolyMatrice {
    private:
        std::vector<std::vector<Poly>> matrice;

    public:
        PolyMatrice() {}  // Constructor
        ~PolyMatrice() {} // Destructor

        void set(int i, int j, Poly value)
        {
            if (i < matrice.size())
            {
                if (j < matrice[i].size())
                {
                    matrice[i][j] = value;
                }
                else
                {
                    matrice[i].push_back(value);
                }
            }
            else
            {
                std::vector<Poly> v;
                v.push_back(value);
                matrice.push_back(v);
            }
        }

        // getter valeur i,j
        Poly get(int i, int j)
        {
            return matrice[i][j];
        }

        size_t sizeRow()
        {
            return matrice.size();
        }

        size_t sizeColumn()
        {
            return matrice[0].size();
        }

        PolyMatrice operator+(PolyMatrice &m)
        {
            PolyMatrice res;
            for (int i = 0; i < matrice.size(); i++)
            {
                for (int j = 0; j < matrice[i].size(); j++)
                {
                    res.set(i, j, matrice[i][j] + m.get(i, j));
                }
            }
            return res;
        }

        PolyMatrice operator*(PolyMatrice &m)
        {
            if (matrice[0].size() != m.sizeRow())
            {
                std::cout << "Multiplication impossible" << std::endl;
                return *this;
            }

            PolyMatrice res;
            for (int i = 0; i < matrice.size(); i++) // On parcourt les lignes de la matrice
            {
                for (int j = 0; j < matrice[i].size(); j++) // On parcourt les colonnes de la matrice
                {
                    res.set(i, j, matrice[i][j] * m.get(i, j));
                }
            }
            return res;
        }
};


class NTTmatrice
{

private:
    std::vector<std::vector<NTT>> matrice;

public:
    NTTmatrice() {}  // Constructor
    ~NTTmatrice() {} // Destructor

    std::vector<NTT> getRow(int i)
    {
        return matrice[i];
    }

    // setter valeur i,j
    void set(int i, int j, NTT value)
    {
        // On vérifie si i est inférieur à la taille de la matrice
        // Si inférieur, on le met à l'index sinon on push_back
        // Puis de même avec j dans le vector à l'index i
        if (i < matrice.size())
        {
            if (j < matrice[i].size())
            {
                matrice[i][j] = value;
            }
            else
            {
                matrice[i].push_back(value);
            }
        }
        else
        {
            std::vector<NTT> v;
            v.push_back(value);
            matrice.push_back(v);
        }
    }

    // getter valeur i,j
    NTT get(int i, int j)
    {
        return matrice[i][j];
    }

    size_t sizeRow()
    {
        return matrice.size();
    }

    // surchage de l'addition de 2 matrices
    NTTmatrice operator+(NTTmatrice &m)
    {
        NTTmatrice res;
        for (int i = 0; i < matrice.size(); i++)
        {
            for (int j = 0; j < matrice[i].size(); j++)
            {
                res.set(i, j, matrice[i][j] + m.get(i, j));
            }
        }
        return res;
    }

    // surchage de la multiplication de 2 matrices
    NTTmatrice operator*(NTTmatrice &m)
    {
        if (matrice[0].size() != m.sizeRow())
        {
            std::cout << "Multiplication impossible" << std::endl;
            return *this;
        }

        NTTmatrice res;
        for (int i = 0; i < matrice.size(); i++)
        {
            for (int j = 0; j < matrice[i].size(); j++)
            {
                res.set(i, j, matrice[i][j] * m.getRow(j)[i]);
            }
        }
        return res;
    }
};

