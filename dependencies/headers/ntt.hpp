// ntt.hpp
#ifndef NTT_HPP
#define NTT_HPP

#include <array>
#include <cstdint>

constexpr std::size_t N = 256;
constexpr uint32_t q = 3329; // 2^12 + 1

std::array<uint32_t, N> ntt(const std::array<uint32_t, N>& f);

#endif // NTT_HPP
