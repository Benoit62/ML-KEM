// ntt.h
#ifndef NTT_inv
#define NTT_inv

#include <vector>
#include <cstdint>

constexpr uint32_t q = 65537; // Modulus

std::vector<uint8_t> ntt_inv(const std::vector<uint8_t>& f_hat);

#endif