#include <cstdint>
#include <vector>

#include <iostream>

using namespace std;


// Définition des constantes ML-KEM-512 
const uint16_t q = 3329;
const uint16_t n = 256;
const uint16_t zeta = 17;  // pas sûr pour uint16_t, à enlever et calculer dans la class Zeta
const uint8_t k = 2;
const uint8_t eta1 = 3;
const uint8_t eta2 = 2;
const uint8_t du = 10;
const uint8_t dv = 4;

typedef long long ll;


// const uint16_t q = 3329;
// const uint16_t n = 8;


class Zeta {
private:

    vector<uint16_t> zetaList;
    vector<uint16_t> gammaList;

    // Calcul le nombre de bits utilisés dans BitRev
    uint8_t findNumBits() {
        uint32_t nTmp = n >> 1;
        uint8_t numBits = 0;
        while (nTmp > 1) {
            nTmp >>= 1;
            numBits++;
        }
        return numBits;
    }

    // Inverse le sens de lecture d'une suite de 2 à 8 bits 
    uint8_t bitRev(uint8_t octet, uint8_t numBits) {
        uint8_t reversedOctet = 0;
        for (uint8_t i = 1 - numBits % 2; i < numBits; i+=2) {
            reversedOctet |= octet << i & 1 << (numBits + i) / 2;
            reversedOctet |= octet >> i & 1 << (numBits - i) / 2;
        }
        return reversedOctet;
    }

    ll mod_pow(ll a, ll n, ll mod) { 
        ll ret = 1; ll p = a % mod; 
        while (n) { 
            if (n & 1) ret = ret * p % mod; 
            p = p * p % mod; 
            n >>= 1; 
        } 
        return ret; 
    }


public:
    // Constructeur
    Zeta() : zetaList(n / 2), gammaList(n / 2) {
        uint8_t numBits = findNumBits();

        for (uint8_t i = 0; i < n / 2; i++) {
            zetaList[i] = mod_pow(17, bitRev(i, numBits), q);
            gammaList[i] = mod_pow(17, 2 * bitRev(i, numBits) + 1, q);
            cout << zetaList[i] << " " << gammaList[i] << endl;
        }
    }

    // Récupère gamma avec l'index i
    uint16_t getZeta(uint8_t i) {
        return zetaList[i];
    }

    // Récupère gamma avec l'index i
    uint16_t getGamma(uint8_t i) {
        return gammaList[i];
    }  
};



