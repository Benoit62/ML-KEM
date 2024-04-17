#include <cstdint>
#include <iostream>
#include <vector>
#include <array>

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Définition des constantes ML-KEM-512
const uint16_t q = 3329;
const uint16_t n = 256;
const uint16_t zeta = 17; // pas sûr pour uint16_t, à enlever et calculer dans la class Zeta
const uint8_t k = 2;
const uint8_t eta1 = 3;
const uint8_t eta2 = 2;
const uint8_t du = 10;
const uint8_t dv = 4;

#endif // CONSTANTS_HPP

class NTTCoef
{
public:
    NTTCoef(uint32_t value = 0) : value(value % q) {}

    NTTCoef &operator+=(const NTTCoef &other)
    {
        value = (value + other.value) % q;
        return *this;
    }

    NTTCoef &operator-=(const NTTCoef &other)
    {
        value = (value + q - other.value) % q;
        return *this;
    }

    NTTCoef &operator*=(const NTTCoef &other)
    {
        value = static_cast<uint32_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other.value) % static_cast<int64_t>(q));
        return *this;
    }

    NTTCoef &operator*=(const uint16_t other){
        value = static_cast<uint16_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other) % static_cast<int64_t>(q));
        return *this;
    }

    friend NTTCoef operator+(NTTCoef lhs, const NTTCoef &rhs);
    friend NTTCoef operator-(NTTCoef lhs, const NTTCoef &rhs);
    friend NTTCoef operator*(NTTCoef lhs, const NTTCoef &rhs);    


    friend std::ostream &operator<<(std::ostream &os, const NTTCoef &coef);

private:
    uint32_t value;
};

NTTCoef operator+(NTTCoef lhs, const NTTCoef &rhs)
{
    lhs += rhs;
    return lhs;
}

NTTCoef operator-(NTTCoef lhs, const NTTCoef &rhs)
{
    lhs -= rhs;
    return lhs;
}

NTTCoef operator*(NTTCoef lhs, const NTTCoef &rhs)
{
    lhs *= rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const NTTCoef &coef)
{
    os << coef.value;
    return os;
}

class PolyCoef
{
public:
    PolyCoef(uint32_t value = 0) : value(value % q) {}

    PolyCoef &operator+=(const PolyCoef &other)
    {
        value = (value + other.value) % q;
        return *this;
    }

    PolyCoef &operator-=(const PolyCoef &other)
    {
        value = (value + q - other.value) % q;
        return *this;
    }

    PolyCoef &operator*=(const PolyCoef &other)
    {
        value = static_cast<uint32_t>(static_cast<int64_t>(value) * static_cast<int64_t>(other.value) % q);
        return *this;
    }

    friend PolyCoef operator+(PolyCoef lhs, const PolyCoef &rhs);
    friend PolyCoef operator-(PolyCoef lhs, const PolyCoef &rhs);
    friend PolyCoef operator*(PolyCoef lhs, const PolyCoef &rhs);

    friend std::ostream &operator<<(std::ostream &os, const PolyCoef &coef);

private:
    uint32_t value;
};

PolyCoef operator+(PolyCoef lhs, const PolyCoef &rhs)
{
    lhs += rhs;
    return lhs;
}

PolyCoef operator-(PolyCoef lhs, const PolyCoef &rhs)
{
    lhs -= rhs;
    return lhs;
}

PolyCoef operator*(PolyCoef lhs, const PolyCoef &rhs)
{
    lhs *= rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const PolyCoef &coef)
{
    os << coef.value;
    return os;
}

class Poly
{
public:
    Poly() {}

    template <std::size_t n>
    Poly(const std::array<NTTCoef, n> &f_hat, const std::array<uint16_t, 128> &zetas)
    {
        std::array<PolyCoef, n> f = f_hat;

        uint32_t k = 127;

        for (uint32_t len = 2; len <= 128; len <<= 1)
        {
            for (uint32_t start = 0; start < 256; start += 2 * len)
            {
                ll zeta = mod_pow(static_cast<ll>(zetas[k]), 1, q);
                k--;

                for (uint32_t j = start; j < start + len; j++)
                {
                    NTTCoef t = f[j];
                    NTTCoef tmp1 = (f[j] + f[j + len]) % q;
                    f[j] = (tmp1 + q) % q;
                    NTTCoef tmp2 = (zeta * (f[j + len] - t)) % q;
                    f[j + len] = (tmp2 + q) % q;
                }
            }
        }

        for (NTTCoef &x : f)
        {
            x = (x * 3303) % q;
        }
        coefficients = f;
    }

    NTTCoef get(std::size_t i) const
    {
        return coefficients[i];
    }

    void set(std::size_t i, const NTTCoef &coef)
    {
        coefficients[i] = coef;
    }

    static Poly SamplePolyCBD_eta(const std::vector<uint8_t> &B, uint32_t eta, uint32_t q)
    {
        Poly result;
        // Implémentation de la fonction SamplePolyCBD_eta
        return result;
    }

private:
    std::array<NTTCoef, n> coefficients;
    const std::size_t maxSize = n;
};

template <typename PolyCoef>
class NTT
{
public:

    NTT();

    template <std::size_t n>

    NTT(const std::array<PolyCoef, n> &f, const std::array<uint16_t, 128> &zetas)
    {
        std::array<uint32_t, N> f_hat = f;

        uint32_t k = 1;

        for (uint32_t len = 128; len >= 2; len /= 2)
        {
            for (uint32_t start = 0; start < N; start += 2 * len)
            {
                uint32_t zeta = mod_pow(17, BitRev7(k), q);
                zetas[k] = zeta;
                k++;

                for (uint32_t j = start; j < start + len; j++)
                {
                    int64_t t = static_cast<int64_t>(zeta) * static_cast<int64_t>(f_hat[j + len]);
                    f_hat[j + len] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) - t % q + q) % q);
                    f_hat[j] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) + t % q) % q);
                }
            }
        }

        coefficients = f_hat;
    }

    PolyCoef get(std::size_t i) const
    {
        return coefficients[i];
    }

    void set(std::size_t i, const PolyCoef &coef)
    {
        coefficients[i] = coef;
    }

    static NTT<PolyCoef> SampleNTT(const XOF &xof)
    {
        // Implémentation de la fonction SampleNTT
    }

    NTT operator*(const NTT &f, const NTT &g) 
    {
        NTT h = MultiplyNTTs(f, g);
        return h;
    }

private:
    std::array<PolyCoef, n> coefficients;
    const std::size_t maxSize = n;

    NTT MultiplyNTTs(const NTT &f, const NTT &g)
    {
        NTT h;

        Zeta primitiveRoot;

        for (uint16_t i = 0; i < n / 2; i++)
        {
            NTTCoef a0 = f.get(2 * i);
            NTTCoef a1 = f.get(2 * i + 1);
            NTTCoef b0 = g.get(2 * i);
            NTTCoef b1 = g.get(2 * i + 1);
            NTTCoef c0;
            NTTCoef c1;

            uint16_t gamma = primitiveRoot.getGamma(i);

            BaseCaseMultiply(a0, a1, b0, b1, c0, c1, gamma);

            h.set(2 * i, c0);
            h.set(2 * i + 1, c1);
        }
        return h;
    }

    void BaseCaseMultiply(const NTTCoef a0, const NTTCoef a1, const NTTCoef b0, const NTTCoef b1, NTTCoef c0, NTTCoef c1, const uint16_t gamma)
    {
        c0 = a0 * b0 + a1 * b1 * gamma;
        c1 = a0 * b1 + a1 * b0;
    }
};








class NTTmatrice
{

private:
    std::vector<std::vector<NTTCoef>> matrice;

public:
    NTTmatrice() {}  // Constructor
    ~NTTmatrice() {} // Destructor

    std::vector<NTTCoef> getRow(int i)
    {
        return matrice[i];
    }

    // setter valeur i,j
    void set(int i, int j, NTTCoef value)
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
            std::vector<NTTCoef> v;
            v.push_back(value);
            matrice.push_back(v);
        }
    }

    // getter valeur i,j
    NTTCoef get(int i, int j)
    {
        return matrice[i][j];
    }

    size_t size()
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
        // Vérification si la multiplication est possible les colonnes de la premiere matrice doit etre egale aux lignes de la 2e
        if (matrice[0].size() != m.size())
        {
            std::cout << "Multiplication impossible" << std::endl;
            return *this;
        }

        NTTmatrice res;
        for (int i = 0; i < matrice.size(); i++)
        {
            for (int j = 0; j < matrice[i].size(); j++)
            {
                NTTCoef sum = 0;
                for (int k = 0; k < matrice.size(); k++)
                {
                    sum += matrice[i][k] * m.get(k, j);
                }
                res.set(i, j, sum);
            }
        }
        return res;
    }
};

NTT f; // Créez un objet NTT
NTT g; // Créez un objet NTT

int main() {

    std::vector<uint16_t> fNTT = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::vector<uint16_t> gNTT = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};


    Poly p;
    // Parcourez chaque élément de fNTT et passez-le à la méthode set de l'objet f
    for (uint16_t element : fNTT) {
        f.set(element);
        g.set(element);
    }
    for (uint16_t i; i < 10; i++) {
        std::cout << f.get(i) << std::endl;
    }
}