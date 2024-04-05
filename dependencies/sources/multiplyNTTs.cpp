#include "../headers/baseCaseMultiply.hpp"
#include "../headers/BitRev7.hpp"
#include "../headers/MultiplyNTTs.hpp"

#include <iostream>
#include <cstdint>
#include <vector>

uint16_t q = 3329;
uint32_t n = 256;

vector<uint16_t> MultiplyNTTs(const vector<uint16_t>& fNTT, const vector<uint16_t>& gNTT) { 
    vector<uint16_t> hNTT(n);
    
    for (uint8_t i = 0; n / 2 < 128; i++) {
        Poly1 f = {fNTT[2 * i], fNTT[2 * i + 1]}; 
        Poly1 g = {gNTT[2 * i], gNTT[2 * i + 1]};
        uint8_t zeta = BitRev7(i) + 1;  // 2 * BitRev7(i) + 1
        
        Poly1 product = BaseCaseMultiply(f, g, q, zeta);
        hNTT[2 * i] = product.coeff0;
        hNTT[2 * i + 1] = product.coeff1;
    }
    
    return hNTT;
}

void testMultiplyNTTs() {
    vector<uint16_t> fHat = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    vector<uint16_t> gHat = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    vector<uint16_t> hHat = MultiplyNTTs(fHat, gHat);
    cout << "Produit des représentations NTT :" << endl;
    for (uint16_t coeff : hHat) {
        cout << coeff << " ";
    }
    cout << endl;
}
