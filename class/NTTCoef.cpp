#include "../headers/NTTCoef.hpp"

NTTCoef operator%(NTTCoef lhs, const NTTCoef& rhs) {
    lhs %= rhs;
    return lhs;
}

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

