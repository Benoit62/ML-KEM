//#include "BitRev7.hpp"
//#include "ntt.hpp"
//#include "test.hpp"

#include <array>
#include <cstdint>

constexpr std::size_t N = 256;

constexpr uint32_t q = 3329; // 2^12 + 1



#include <iostream>
//n = 2   q = 3    zeta = -1
//n = 4  q = 5    zeta = 2
typedef long long ll;

ll mod_pow(ll a, ll n, ll mod) { ll ret = 1; ll p = a % mod; while (n) { if (n & 1) ret = ret * p % mod; p = p * p % mod; n >>= 1; } return ret; }

uint32_t zetas[128] = { 1 };

std::array<uint32_t, N> ntt(const std::array<uint32_t, N>& f) {

    std::array<uint32_t, N> f_hat = f;

    uint32_t k = 1;

    for (uint32_t len = 128; len >= 2; len /= 2) {

        for (uint32_t start = 0; start < N; start += 2 * len) {

            uint32_t zeta = mod_pow(17, BitRev7(k), q);
            zetas[k] = zeta;
            k++;
            //std::cout << " zeta = " << zeta;

            for (uint32_t j = start; j < start + len; j++) {

                uint32_t t = zeta * f_hat[j + len] % q;

                f_hat[j + len] = (f_hat[j] - t) % q;

                f_hat[j] = (f_hat[j] + t) % q;

            }

        }

    }
    for (size_t i = 0; i < 128; i++) {
        std::cout << zetas[i] << " ";
    }
    std::cout << std::endl;

    return f_hat;

}

std::array<uint32_t, 4> ntt_simplifie(const std::array<uint32_t, 4>& f) {

    std::array<uint32_t, 4> f_hat = f;

    uint32_t k = 1;

    for (uint32_t len = 2; len >= 2; len /= 2) {

        for (uint32_t start = 0; start < 4; start += 2 * len) {

            uint32_t zeta = mod_pow(2, BitRev7(k), 5);
            zetas[k - 1] = zeta;
            k++;
            //std::cout << "k = " <<k;

            for (uint32_t j = start; j < start + len; j++) {

                uint32_t t = zeta * f_hat[j + len] % 5;

                f_hat[j + len] = (f_hat[j] - t) % 5;

                f_hat[j] = (f_hat[j] + t) % 5;

            }

        }

    }

    return f_hat;

}


std::array<ll, 4> ntt_inv_simple(const std::array<ll, 4>& f_hat) {
    std::array<ll, 4> f = f_hat;

    uint32_t k = 2;

    for (uint32_t len = 2; len <= 2; len <<= 1) {
        for (uint32_t start = 0; start < 2; start += 2 * len) {
            //ll zeta = mod_pow(zetas[BitRev7(k)], 1, q);
            //ll zeta = mod_pow(zetas[k], BitRev7(k), q);
            ll zeta = zetas[k - 1];
            //uint32_t zeta = mod_pow(17, BitRev7(k), q);
            k--;

            for (uint32_t j = start; j < start + len; j++) {
                ll t = f[j];
                f[j] = (t + f[j + len]) % 5;
                f[j + len] = (zeta * (f[j + len] - t)) % 5;
            }
        }
    }

    for (ll& x : f) {
        x = (x * 3) % 5;
    }

    return f;
}




std::array<ll, 256> ntt_inv(const std::array<ll, 256>& f_hat) {
    std::array<ll, 256> f = f_hat;

    uint32_t k = 127;

    for (uint32_t len = 2; len <= 128; len <<= 1) {
        for (uint32_t start = 0; start < 256; start += 2 * len) {
            //ll zeta = mod_pow(zetas[BitRev7(k)], 1, q);
            //ll zeta = mod_pow(zetas[k], BitRev7(k), q);
            ll zeta = zetas[k - 1];
            //uint32_t zeta = mod_pow(17, BitRev7(k), q);
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

int testNTT0() {
    std::array<ll, 256> f_hat = { 0 };  // Tableau d'entrée rempli de 0

    std::array<ll, 256> recovered = ntt_inv(f_hat);

    // Vérifier que la sortie est bien un tableau de 0
    for (ll x : recovered) {
        if (x != 0) {
            std::cout << "Erreur : la sortie contient une valeur non nulle" << std::endl;
            return 1;
        }
    }

    std::cout << "Test réussi !" << std::endl;
    return 0;
}

int testNTTsimple() {

        std::array<uint32_t, 256> input = { 0 };

        input[0] = 1;
        input[3] = 1;
        //for (size_t i = 0; i < 256; i = i+2) {
        //    input[i] = 1;
        //}

        std::cout << "input :" << std::endl;
        for (size_t i = 0; i < 256; i++) {
            std::cout << input[i] << " ";
        }
        std::cout << std::endl;

        std::array<uint32_t, 256> transformed = ntt(input);

        // Afficher les éléments du résultat
        std::cout << "Résultat de la NTT :" << std::endl;
        for (size_t i = 0; i < 256; i++) {
            std::cout << transformed[i] << " ";
        }
        std::cout << std::endl;

        // Effectuer la NTT inverse
        std::array<ll, 256> transformed_ll;
        for (size_t i = 0; i < 256; i++) {
            transformed_ll[i] = transformed[i];
        }

        std::array<ll, 256> recovered = ntt_inv(transformed_ll);

        // Afficher les premiers éléments du résultat inverse
        std::cout << "Résultat de la NTT inverse :" << std::endl;
        for (size_t i = 0; i < 256; i++) {
            std::cout << recovered[i] << " ";
        }
        std::cout << std::endl;

        return 0;
    
}

int testNTTsimpleV2() {

    std::array<uint32_t, 4> input = { 1,1,1,0 };

    //input[0] = 1;
    //input[1] = 1;
    //for (size_t i = 0; i < 256; i = i+2) {
    //    input[i] = 1;
    //}

    std::cout << "input :" << std::endl;
    for (size_t i = 0; i < 4; i++) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;

    std::array<uint32_t, 4> transformed = ntt_simplifie(input);

    // Afficher les éléments du résultat
    std::cout << "Résultat de la NTT :" << std::endl;
    for (size_t i = 0; i < 4; i++) {
        std::cout << transformed[i] << " ";
    }
    std::cout << std::endl;

    // Effectuer la NTT inverse
    std::array<ll, 4> transformed_ll;
    for (size_t i = 0; i < 4; i++) {
        transformed_ll[i] = transformed[i];
    }

    std::array<ll, 4> recovered = ntt_inv_simple(transformed_ll);

    // Afficher les premiers éléments du résultat inverse
    std::cout << "Résultat de la NTT inverse :" << std::endl;
    for (size_t i = 0; i < 4; i++) {
        std::cout << recovered[i] << " ";
    }
    std::cout << std::endl;

    return 0;

}


void testNTT_invRemi() {
    std::array<ll, 256> input = { 0 };

    input[2] = 2;
    std::array<ll, 256> f = ntt_inv(input);
    std::cout << "Résultat de la NTT inverse :" << std::endl;
    for (size_t i = 0; i < 256; i++) {
        std::cout << f[i] << " ";
    }
    std::cout << std::endl;
}

int testNTTWithZeroInput() {
    std::array<uint32_t, 256> input = { 0 };

    // Remplir les 8 premiers éléments avec 1, 2, 3, 4, 5, 6, 7, 8
    input[0] = 1;
    input[1] = 2;
    input[2] = 3;
    input[3] = 4;
    input[4] = 5;
    input[5] = 6;
    input[6] = 7;
    input[7] = 8;

    std::array<uint32_t, 256> transformed = ntt(input);

    std::cout << "valeur NTT : " << std::endl;
    for (uint32_t x : transformed) {
        std::cout << x << " ";
    }

    std::cout << "Test réussi !" << std::endl;
    return 0;
}

uint8_t BitRev7(uint8_t n) {
    if (n >> 7 != 0) {
        // Handle error condition (e.g., throw an exception)
        //throw std::runtime_error("not 7 bits");
    }

    uint8_t r = 0;
    r |= (n >> 6) & 0b00000001;
    r |= (n >> 4) & 0b00000010;
    r |= (n >> 2) & 0b00000100;
    r |= (n) & 0b00001000;
    r |= (n << 2) & 0b00010000;
    r |= (n << 4) & 0b00100000;
    r |= (n << 6) & 0b01000000;

    return r;
}


int main() {
    //testBothNTT();
    //testNTT0();
    //testNTTsimple();
    testNTTsimpleV2();
    //testNTT_invRemi();
    //testNTTWithZeroInput();
    return 0;
}