#include <cassert>
#include <iostream>
#include "../headers/byteDecode.hpp"

vector<uint32_t> byteDecode(const vector<uint8_t>& B, uint32_t d) {
    vector<bool> b = bytesToBits(B);
    uint32_t m = (d < 12) ? (1 << d) : 3329;

    vector<uint32_t> F(256);

    for (int i = 0; i < 256; i++) {
        uint32_t sum = 0;
        for (int j = 0; j < d; j++) {
            sum += b[i * d + j] * (1 << j);
        }
        F[i] = sum % m;
    }
    return F;
}

// passe pas les tests
void testByteDecode() {
    // Test case 1: Empty vector
    vector<uint8_t> emptyBytes;
    uint32_t d = 4;
    vector<uint32_t> emptyResult = byteDecode(emptyBytes, d);
    assert(emptyResult.empty());

    // Test case 2: Single block, d = 4
    vector<uint8_t> singleBlock = {0b10101010, 0b01010101, 0b11111111, 0b00000000,
                                   0b10101010, 0b01010101, 0b11111111, 0b00000000};
    d = 4;
    vector<uint32_t> expectedSingle = {10, 5, 15, 0, 10, 5, 15, 0};
    vector<uint32_t> singleResult = byteDecode(singleBlock, d);
    assert(singleResult == expectedSingle);

    // Test case 3: Multiple blocks, d = 8
    vector<uint8_t> multipleBlocks = {0b10101010, 0b01010101, 0b11111111, 0b00000000,
                                      0b10101010, 0b01010101, 0b11111111, 0b00000000,
                                      0b10101010, 0b01010101, 0b11111111, 0b00000000,
                                      0b10101010, 0b01010101, 0b11111111, 0b00000000};
    d = 8;
    vector<uint32_t> expectedMultiple = {170, 85, 255, 0, 170, 85, 255, 0,
                                         170, 85, 255, 0, 170, 85, 255, 0};
    vector<uint32_t> multipleResult = byteDecode(multipleBlocks, d);
    assert(multipleResult == expectedMultiple);

    cout << "All tests passed!" << endl;
}