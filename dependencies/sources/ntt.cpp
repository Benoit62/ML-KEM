#include <iostream>
#include <vector>
#include <cstdint>

// Fonction pour calculer la NTT en place
void computeNTT(std::vector<int>& f, int q) {
    int n = f.size();
    int k = 1;
    for (int len = 128; len >= 2; len /= 2) {
        for (int start = 0; start < n; start += 2 * len) {
            int zeta = BitRev7(k) % q;
            k++;
            for (int j = start; j < start + len; j++) {
                int t = (1LL * zeta * f[j + len]) % q;
                f[j + len] = (f[j] - t + q) % q;
                f[j] = (f[j] + t) % q;
            }
        }
    }
}

// Fonction BitRev7 (supposée déjà implémentée)
uint8_t BitRev7(uint8_t i);

void testComputeNTT() {
    // Définissez ici vos cas de test
    std::vector<std::vector<int>> testCases = {
        // Cas 1: polynôme de degré 0
        {1},
        // Cas 2: polynôme de degré 1
        {1, 2},
        // Cas 3: polynôme de degré supérieur
        {1, 2, 3, 4, 5}
    };

    std::vector<std::vector<int>> expectedResults = {
        // Résultat attendu pour le cas 1
        {1},
        // Résultat attendu pour le cas 2
        {1, 2},
        // Résultat attendu pour le cas 3
        {1, 2, 3, 4, 5}
    };

    int modulus = 256; // Modulo utilisé pour les tests

    // Boucle pour exécuter les cas de test
    for (size_t i = 0; i < testCases.size(); i++) {
        std::vector<int> inputPolynomial = testCases[i];
        std::vector<int> expectedResult = expectedResults[i];

        // Appel de computeNTT
        computeNTT(inputPolynomial, modulus);

        // Vérification du résultat
        if (inputPolynomial == expectedResult) {
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
