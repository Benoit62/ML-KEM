#include "../headers/NTT_inv.hpp"
#include "../headers/BitRev7.hpp"

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