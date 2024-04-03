// ntt.cpp
#include "../headers/ntt.hpp"
#include "../headers/BitRev7.hpp"

std::array<uint32_t, N> ntt(const std::array<uint32_t, N>& f) {
    std::array<uint32_t, N> f_hat = f;

    uint32_t k = 1;
    for (uint32_t len = 128; len >= 2; len /= 2) {
        for (uint32_t start = 0; start < N; start += 2 * len) {
            uint32_t zeta = BitRev7(k) % q;
            k++;

            for (uint32_t j = start; j < start + len; j++) {
                uint32_t t = zeta * f_hat[j + len] % q;
                f_hat[j + len] = (f_hat[j] - t) % q;
                f_hat[j] = (f_hat[j] + t) % q;
            }
        }
    }

    return f_hat;
}
