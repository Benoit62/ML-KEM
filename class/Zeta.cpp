#include "../headers/Zeta.hpp"

// Calcul le nombre de bits utilisés dans BitRev
uint8_t Zeta::findNumBits() {
    uint32_t nTmp = n >> 1;
    uint8_t numBits = 0;
    while (nTmp > 1) {
        nTmp >>= 1;
        numBits++;
    }
    return numBits;
}

// Inverse le sens de lecture d'une suite de 2 à 8 bits 
uint8_t Zeta::bitRev(uint8_t octet, uint8_t numBits) {
    uint8_t reversedOctet = 0;
    for (uint8_t i = 1 - numBits % 2; i < numBits; i+=2) {
        reversedOctet |= octet << i & 1 << (numBits + i) / 2;
        reversedOctet |= octet >> i & 1 << (numBits - i) / 2;
    }
    return reversedOctet;
}

uint16_t Zeta::mod_pow(ll a, ll n, ll mod) { 
    ll ret = 1; ll p = a % mod; 
    while (n) { 
        if (n & 1) ret = ret * p % mod; 
        p = p * p % mod; 
        n >>= 1; 
    } 
    return ret; 
}

uint16_t Zeta::findSmallestPrimitiveRoot() {
    for (uint16_t i = 2; i < q; i++) {
        if (mod_pow(i, n / 2, q) == q - 1) {
            return i;
        }
    }
    return q;  // S'il nexiste pas de racine primitive
}

// Constructeur
Zeta::Zeta() {
    uint8_t numBits = findNumBits();

    uint16_t primitiveRoot = findSmallestPrimitiveRoot();  // Constante noté zeta dans le FIPS
    // cout << primitiveRoot << endl;

    for (uint8_t i = 0; i < n / 2; i++) {
        zetaList[i] = mod_pow(primitiveRoot, bitRev(i, numBits), q);
        gammaList[i] = mod_pow(primitiveRoot, 2 * bitRev(i, numBits) + 1, q);
        // cout << zetaList[i] << " " << gammaList[i] << endl;
    }
}

// Récupère gamma avec l'index i
uint16_t Zeta::getZeta(uint16_t i) {
    return zetaList[i];
}

// Récupère gamma avec l'index i
uint16_t Zeta::getGamma(uint16_t i) {
    return gammaList[i];
}
