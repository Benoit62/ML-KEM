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

    vector<vector<vector<uint32_t>>> A;
    for(int i=0; i<k;i++) {
        for(int j=0; j<k; j++) {       
            A[i][j] = SampleNTT(XOF(rho, i, j));
        }
    }

    vector<vector<uint32_t>> s;
    for(int i=0;i<k;i++) {
        s[i] = SamplePolyCBD_eta(PRF(sigma, N, eta1),eta1,q);
        N++;
    }

    vector<vector<uint32_t>> e;
    for(int i=0;i<k;i++) {
        e[i] = SamplePolyCBD_eta(PRF(sigma, N, eta1), eta1, q);
        N++;
    }

    // TODO check with NTT func cause seems weird
    // TODO overload multiplication for matrix * vector
    // TODO overload vector addition

    // prints outputs for debug
    cout << "A = ";
    for(uint32_t i=0;i<k;i++) {
        for(uint32_t j=0;j<k;j++) {
            for(uint32_t elem:A[i][j]) cout << A[i][j][elem] << " ";
        }
        cout << endl;
    }

    cout << "s = ";
    for(uint32_t i=0;i<k;i++) {
        for(uint32_t elem:s[i]) cout << s[i][elem] << " "; 
    }

    cout << endl << "e = ";
    for(uint32_t i=0;i<k;i++) {
        for(uint32_t elem:e[i]) cout << e[i][elem] << " "; 
    }

    return digest;
}