#include <iostream>
#include <vector>
#include <cmath>

uint32_t q = 3329; 
std::vector<int> SampleNTT(const std::vector<unsigned char>& B) {
    std::vector<int> a;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t d1, d2;

    while (j < 256) {
        d1 = B[i] + 256 * (B[i + 1] % 16);
        d2 = static_cast<int>(floor(B[i + 1] / 16.0)) + 16 * B[i + 2];

        if (d1 < q) {
            a.push_back(d1);
            j++;
        }

        if (d2 < q && j < 256) {
            a.push_back(d2);
            j++;
        }
        i += 3;
    }

    return a;
}
