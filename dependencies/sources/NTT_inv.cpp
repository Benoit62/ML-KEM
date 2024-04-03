#include <vector>
#include <cstdint>
#include <iostream>

#include "../headers/BitRev7.hpp"

constexpr uint32_t q = 65537; // Modulus
constexpr uint32_t zetas[128] = { /* Table des racines de l'unité modulo q */ };

std::vector<uint8_t> ntt_inv(const std::vector<uint8_t>& f_hat) {
    std::vector<uint8_t> f = f_hat;
    uint32_t k = 127;

    for (uint32_t len = 2; len <= 128; len <<= 1) {
        for (uint32_t start = 0; start < 256; start += 2 * len) {
            uint32_t zeta = zetas[BitRev7(k)] % q;
            k--;

            for (uint32_t j = start; j < start + len; j++) {
                uint8_t t = f[j];
                f[j] = static_cast<uint8_t>((t + f[j + len]) % q);
                f[j + len] = static_cast<uint8_t>(zeta * static_cast<uint32_t>(f[j + len] - t) % q);
            }
        }
    }

    for (uint8_t& x : f) {
        x = static_cast<uint8_t>((static_cast<uint32_t>(x) * 3303) % q);
    }

    return f;
}

void testNttInv() {
    std::vector<std::vector<uint32_t>> testCases = {
        {0},                                   // Cas trivial
        {1, 2, 3, 4},                          // Cas avec quelques coefficients
        {255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} // Cas avec un seul coefficient non nul
    };

    std::vector<std::vector<uint32_t>> expectedResults = {
        {0},
        {1, 65536, 65535, 65534},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (size_t i = 0; i < testCases.size(); i++) {
        std::vector<uint8_t> f_hat(testCases[i].begin(), testCases[i].end());
        std::vector<uint8_t> result = ntt_inv(f_hat);
        std::vector<uint32_t> resultWide(result.begin(), result.end());
        if (resultWide == expectedResults[i]) {
            std::cout << "Test case " << i << " passed." << std::endl;
        } else {
            std::cout << "Test case " << i << " failed." << std::endl;
            std::cout << "Input: ";
            for (uint32_t coeff : testCases[i]) {
                std::cout << coeff << " ";
            }
            std::cout << std::endl;
            std::cout << "Expected: ";
            for (uint32_t coeff : expectedResults[i]) {
                std::cout << coeff << " ";
            }
            std::cout << std::endl;
            std::cout << "Result: ";
            for (uint32_t coeff : resultWide) {
                std::cout << coeff << " ";
            }
            std::cout << std::endl;
        }
    }
}
