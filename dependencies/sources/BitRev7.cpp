#include "../headers/BitRev7.hpp"
#include <iostream>

using namespace std;

/*uint32_t BitRev7(uint32_t x) {
    x = (x & 0x00000000ffffffffU) << 16 | (x & 0xffffffff00000000U) >> 16;
    x = (x & 0x0000ffff0000ffffU) << 8 | (x & 0xffff0000ffff0000U) >> 8;
    x = (x & 0x00ff00ff00ff00ffU) << 4 | (x & 0xff00ff00ff00ff00U) >> 4;
    x = (x & 0x0f0f0f0f0f0f0f0fU) << 2 | (x & 0xf0f0f0f0f0f0f0f0U) >> 2;
    x = (x & 0x3333333333333333U) << 1 | (x & 0xccccccccccccccccU) >> 1;
    return x;
}*/

uint8_t BitRev7(uint8_t n) {
    if (n >> 7 != 0) {
        // Handle error condition (e.g., throw an exception)
        //throw std::runtime_error("not 7 bits");
    }

    uint8_t r = 0;
    r |= (n >> 6) & 0b00000001;
    r |= (n >> 4) & 0b00000010;
    r |= (n >> 2) & 0b00000100;
    r |= (n     ) & 0b00001000;
    r |= (n << 2) & 0b00010000;
    r |= (n << 4) & 0b00100000;
    r |= (n << 6) & 0b01000000;

    return r;
}

// // Calcul le nombre de bits utilisés dans BitRev
// uint8_t findNumBits() {
//     uint32_t nTmp = n >> 1;  // constante à rajouter
//     uint8_t numBits = 0;
//     while (nTmp > 1) {
//         nTmp >>= 1;
//         numBits++;
//     }
//     return numBits;
// }

// // Inverse le sens de lecture d'une suite de 2 à 8 bits 
// uint8_t BitRev(uint8_t octet, uint8_t numBits) {
//     uint8_t reversedOctet = 0;
//     for (uint8_t i = 1 - numBits % 2; i < numBits; i+=2) {
//         reversedOctet |= octet << i & 1 << (numBits + i) / 2;
//         reversedOctet |= octet >> i & 1 << (numBits - i) / 2;
//     }
//     return reversedOctet;
// }

// void testBitRev(uint32_t n) {
//     uint8_t numBits = findNumBits();

//     for (uint8_t i = 0; i < n / 2; i++) {
//         cout << static_cast<int>(BitRev(i, numBits)) << endl;
//     }

// }
