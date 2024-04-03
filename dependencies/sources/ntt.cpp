#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include "../headers/NTT.hpp"
#include "../headers/BitRev7.hpp"

int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void precomputeRoots(int* roots, int q, int n) {
    int root = modPow(3, (q - 1) / n, q);
    roots[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        roots[i] = (roots[i + 1] * root) % q;
    }
}

void computeNTT(std::vector<int>& f, int q) {
    int n = f.size();
    std::vector<int> result(f); // Créer une copie du polynôme d'entrée

    // Réorganisation des coefficients en ordre de bits inversés
    for (int i = 0; i < n; i++) {
        int j = BitRev7(i) >> (8 - static_cast<int>(log2(n) + 1));
        if (i < j)
            std::swap(result[i], result[j]);
    }

    int* roots = new int[n + 1];
    precomputeRoots(roots, q, n);

    for (int len = 2; len <= n; len <<= 1) {
        int half_len = len >> 1;
        int zeta = roots[half_len];
        int zeta_exp = 1;
        for (int start = 0; start < n; start += len) {
            for (int j = start; j < start + half_len; j++) {
                int t = (zeta_exp * result[j + half_len]) % q;
                result[j] = (result[j] + t) % q;
                result[j + half_len] = (result[j] - t + q) % q;
                zeta_exp = (zeta_exp * zeta) % q;
            }
        }
    }

    f = result;
    delete[] roots;
}

void testComputeNTT() {
    std::vector<std::vector<int>> testCases = {
        {1}, {1, 2}, {1, 2, 3, 4, 5}
    };

    std::vector<std::vector<int>> expectedResults = {
        {1}, {3, 10}, {15, 20, 9, 12, 5}
    };

    int modulus = 256;
    for (size_t i = 0; i < testCases.size(); i++) {
         std::cout << "Bonjour, monde 1 !" << std::endl;
        std::vector<int> inputPolynomial = testCases[i];
         std::cout << "Bonjour, monde 2!" << std::endl;
        std::vector<int> expectedResult = expectedResults[i];
         std::cout << "Bonjour, monde 3!" << std::endl;

        computeNTT(inputPolynomial, modulus);
            std::cout << "Bonjour, monde 4!" << std::endl;

        if (inputPolynomial == expectedResult) {
             std::cout << "Bonjour, monde 5!" << std::endl;
            std::cout << "Test case " << i << " passed." << std::endl;
        } else {
            std::cout << "Test case " << i << " failed." << std::endl;
            std::cout << "Input: ";
            for (int coeff : inputPolynomial) {
                std::cout << coeff << " ";
            }
            std::cout << std::endl;
            std::cout << "Expected: ";
            for (int coeff : expectedResult) {
                std::cout << coeff << " ";
            }
            std::cout << std::endl;
        }
    }
}
