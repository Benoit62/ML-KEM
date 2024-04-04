#ifndef NTT_HPP
#define NTT_HPP

#include <vector>
#include <cstdint>

constexpr uint32_t q = 7;
typedef long long ll;

std::vector<ll> ntt(const std::vector<ll>& f, int sign);
std::vector<ll> convolution(const std::vector<ll>& a, const std::vector<ll>& b);

#endif // NTT_HPP
