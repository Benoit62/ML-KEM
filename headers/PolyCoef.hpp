#pragma once

#ifndef POLY_COEF_HPP
#define POLY_COEF_HPP

#include <iostream>
#include "constants.hpp"


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

#endif