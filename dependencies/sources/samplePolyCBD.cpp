#include <vector>
#include <cstdint>
#include "../headers/bytesToBits.hpp"

using namespace std;

vector<uint32_t> SamplePolyCBD_eta(const vector<unsigned char>& B, uint32_t eta, uint32_t q) {
    vector<bool> b = bytesToBits(B);
    vector<uint32_t> f(256);

    for (int i = 0; i < 256; i++) {
        uint32_t x = 0;
        uint32_t y = 0;

        for (int j = 0; j < eta; j++) {
            x += b[2 * i * eta + j];
            y += b[2 * i * eta + eta + j];
        }

        f[i] = (x - y + q) % q;
    }
    return f;
}