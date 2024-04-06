#include <vector>
#include <cstdint>
#include <iostream>
#include <array>

#include "../headers/BitRev7.hpp"
#include "../headers/NTT.hpp"

typedef long long ll;
constexpr uint32_t q = 65537; // Modulus
constexpr uint32_t zetas[128] = { /* Table des racines de l'unité modulo q */ };

ll mod_pow(ll a, ll n, ll mod) { ll ret = 1; ll p = a % mod; while (n) { if (n & 1) ret = ret * p % mod; p = p * p % mod; n >>= 1; } return ret; }

std::array<ll, 256> ntt_inv(const std::array<ll, 256>& f_hat) {
    std::array<ll, 256> f = f_hat;

    uint32_t k = 127; // 2: k ← 127

    for (uint32_t len = 2; len <= 128; len <<= 1) {
        for (uint32_t start = 0; start < 256; start += 2 * len) {
            ll zeta = mod_pow(zetas[BitRev7(k)], 1, q);
            k--; 

            for (uint32_t j = start; j < start + len; j++) {
                ll t = f[j];
                f[j] = (t + f[j + len]) % q;
                f[j + len] = (zeta * (f[j + len] - t)) % q;
            }
        }
    }

    for (ll& x : f) {
        x = (x * 3303) % q;
    }

    return f;
}

int testBothNTT() {
    std::array<uint32_t, 256> input;
    // Initialiser le tableau d'entrée avec des valeurs quelconques
    for (auto& x : input) {
        x = rand() % q;
    }

    std::array<uint32_t, 256> transformed = ntt(input);
    std::array<ll, 256> transformed_ll;
    // Copier les valeurs de transformed dans transformed_ll
    for (size_t i = 0; i < 256; i++) {
        transformed_ll[i] = transformed[i];
    }

    std::array<ll, 256> recovered = ntt_inv(transformed_ll);

    // Vérifier que l'entrée est bien récupérée après la transformation et l'inverse
    for (size_t i = 0; i < 256; i++) {
        if (static_cast<uint32_t>(recovered[i]) != input[i]) {
            std::cout << "Erreur à l'indice " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test réussi !" << std::endl;
    return 0;
}