#ifndef ZETA_HPP
#define ZETA_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include "constants.hpp"

using namespace std;

typedef long long ll;

vector<uint16_t> zetaList(n / 2);
vector<uint16_t> gammaList(n / 2);

class Zeta {
    private:
        uint8_t findNumBits();
        uint8_t bitRev(uint8_t octet, uint8_t numBits);
        uint16_t mod_pow(ll a, ll n, ll mod);
        uint16_t findSmallestPrimitiveRoot();
    
    public:
        Zeta();
        uint16_t getZeta(uint16_t i);
        uint16_t getGamma(uint16_t i);
};

#endif