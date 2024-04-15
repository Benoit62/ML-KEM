// ntt.cpp
#include "../headers/ntt.hpp"
#include <iostream>
#include "../headers/NTT_inv.hpp"
#include "../headers/BitRev7.hpp"

typedef long long ll;
uint32_t zetas[128] = { /* Table des racines de l'unité modulo q */ };

ll mod_pow(ll a, ll n, ll mod) { ll ret = 1; ll p = a % mod; while (n) { if (n & 1) ret = ret * p % mod; p = p * p % mod; n >>= 1; } return ret; }
std::array<uint32_t, N> ntt(const std::array<uint32_t, N>& f) {
    std::array<uint32_t, N> f_hat = f;

    uint32_t k = 1;

    for (uint32_t len = 128; len >= 2; len /= 2) {
        for (uint32_t start = 0; start < N; start += 2 * len) {
            uint32_t zeta = mod_pow(17, BitRev7(k), q);
            zetas[k] = zeta;
            k++;

            for (uint32_t j = start; j < start + len; j++) {
                int64_t t = static_cast<int64_t>(zeta) * static_cast<int64_t>(f_hat[j + len]);
                f_hat[j + len] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) - t % q + q) % q);
                f_hat[j] = static_cast<uint32_t>((static_cast<int64_t>(f_hat[j]) + t % q) % q);
            }
        }
    }

    return f_hat;
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
