#pragma once

#ifndef NTT_HPP
#define NTT_HPP

#include <iostream>

#include "Poly.hpp"
#include "XOF.hpp"

class NTT{
    private:
        std::array<NTTCoef, n> coefficients;
        NTT MultiplyNTTs(const NTT& f, const NTT& g);
        void BaseCaseMultiply(const NTTCoef a0, const NTTCoef a1, const NTTCoef b0, const NTTCoef b1, NTTCoef& c0, NTTCoef& c1, const uint16_t gamma);

    public:
        NTT();
        template <std::size_t n>
        NTT(const Poly& t);
        template <std::size_t n>
        NTT(const std::array<NTTCoef, n>& input);
        NTTCoef get(std::size_t i) const;
        void set(std::size_t i, const NTTCoef& coef);
        static NTT SampleNTT(XOF B);
        std::array<NTTCoef, n> getCoef();
        NTT& operator=(const NTT& other);
        NTT& operator*(const NTT& other);
        NTT& operator+(const NTT& other);
        static void testNTT();
};

#endif