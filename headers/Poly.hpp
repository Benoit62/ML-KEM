#pragma once

#ifndef POLY_HPP
#define POLY_HPP

#include <vector>
#include <array>

#include "NTT.hpp"
#include "NTTCoef.hpp"
#include "ByteArray.hpp"


class Poly
{
private:
    std::array<NTTCoef, n> coefficients;

public:
    Poly();
    template <std::size_t n>
    Poly(const NTT& f_hat);
    NTTCoef get(std::size_t i) const;
    void set(std::size_t i, const NTTCoef& coef);
    static Poly SamplePolyCBD_eta(const ByteArray& B, uint32_t eta, uint32_t q);
    std::array<NTTCoef, n> getCoef();
    Poly& operator=(const Poly& other);
    Poly& operator+(const Poly& other);
};

#endif