#include "../headers/PolyCoef.hpp"

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