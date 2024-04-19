#pragma once

#ifndef NTT_COEF_HPP
#define NTT_COEF_HPP

#include <iostream>
#include "constants.hpp"

class NTTCoef {
    private:
        uint16_t value;

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

};

#endif