#include <cassert>
#include <iostream>
#include <algorithm>
#include "../headers/bytesToBits.hpp"

using namespace std;

vector<bool> bytesToBits(const vector<uint8_t>& B) {
    vector<uint8_t> Bytes = B;
    size_t l = B.size();
    vector<bool> b(8 * l);

    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < 8; j++) {
            b[8 * i + j] = Bytes[i] % 2;
            Bytes[i] = Bytes[i] / 2;
        }
        reverse(b.begin()+8*i, b.begin()+8*i+8);
    }
    return b;
}

void testBytesToBits() {
    // Test case 1: Empty vector
    vector<uint8_t> emptyBytes;
    vector<bool> emptyBits = bytesToBits(emptyBytes);
    assert(emptyBits.empty());

    // Test case 2: Single byte
    vector<uint8_t> singleByte = {0b10101010};
    vector<bool> singleBits = bytesToBits(singleByte);
    vector<bool> expectedSingleBits = {1,0,1,0,1,0,1,0};
    assert(singleBits == expectedSingleBits);

    // Test case 3: Multiple bytes
    vector<uint8_t> multipleBytes = {0b10101010, 0b01010101, 0b11111111, 0b00000000};
    vector<bool> multipleBits = bytesToBits(multipleBytes);
    vector<bool> expectedMultipleBits = {1, 0, 1, 0, 1, 0, 1, 0,
                                         0, 1, 0, 1, 0, 1, 0, 1,
                                         1, 1, 1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0};
    assert(multipleBits == expectedMultipleBits);

    cout << "All tests passed!" << endl;
}