#include <cryptopp/sha3.h>
#include <cryptopp/shake.h>
#include "../headers/KPKE.KeyGen.hpp"

uint32_t k = 2;
uint32_t q = 3329;
uint32_t n = 256;
uint32_t eta1 = 3;
uint32_t eta2 = 2;
uint32_t du = 10;
uint32_t dv = 4;

pair<vector<uint8_t>, vector<uint8_t>> KPKE_KeyGen() {
    vector<uint8_t> d = generateRandomBytes(32);

    pair<vector<uint8_t>, vector<uint8_t>> digest = G(d);
    vector<uint8_t> rho = digest.first;
    vector<uint8_t> sigma = digest.second;

    int N = 0;

    for(int i=0; i<k;i++) {
        for(int j=0; j<k; j++) {       
            vector<int> A[i,j] = SampleNTT(XOF(rho, i, j));
        }
    }

    for(int i=0;i<k;i++) {
        vector<uint32_t> s[i] = SamplePolyCBD_eta(PRF(sigma, N, eta1),eta1,q);
        N++;
    }

    for(int i=0;i<k;i++) {
        vector<uint32_t> e[i] = SamplePolyCBD_eta(PRF(sigma, N, eta1), eta1, q);
        N++;
    }

    // TODO check with NTT func cause seems weird
    // TODO overload multiplication for matrix * vector
    // TODO overload vector addition
}