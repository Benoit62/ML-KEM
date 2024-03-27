#include <vector>
#include <cmath>
#include <cstdint>
#include "../headers/bytesToBits.hpp"

vector<uint64_t> byteDecode(const vector<unsigned char>& B, int d) {
    vector<bool> b = bytesToBits(B);
    uint64_t m = (d < 12) ? (1 << d) : 3329; // q = 3329 for d = 12

    vector<uint64_t> F(256);

    for (int i = 0; i < 256; i++) {
        uint64_t sum = 0;
        for (int j = 0; j < d; j++) {
            sum += b[i * d + j] * (1 << j);
        }
        F[i] = sum % m;
    }
    return F;
}