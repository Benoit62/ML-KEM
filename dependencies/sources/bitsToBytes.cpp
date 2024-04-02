#include <iostream>
#include <vector>
#include <cstdint>

std::vector<unsigned char> bitsToBytes(const std::vector<bool>& bits) {
    // Convertit un vecteur de bits en un vecteur d'octets
    // Attention : le nombre de bits doit être un multiple de 8 pour éviter les erreurs vu que le LSB est le premier bit du vecteur
    // Le LSB doit être le premier bit du vecteur (LSB = Least Significant Bit, bit de poids faible)

    std::vector<unsigned char> bytes;
    unsigned char byte = 0;
    int bitIndex = 0;

    for (bool bit : bits) {
        byte |= static_cast<unsigned char>(bit) << bitIndex;
        bitIndex++;

        if (bitIndex == 8) {
            bytes.push_back(byte);
            byte = 0;
            bitIndex = 0;
        }
    }

    if (bitIndex > 0) {
        bytes.push_back(byte);
    }

    return bytes;
}

void testBitsToBytes() {
    std::vector<bool> testCases[] = {
        {},                                                 // Cas vide
        {0},                                                // Un seul bit à 0
        {1},                                                // Un seul bit à 1
        {1,0,1},                                            // Cas avec plusieurs bits mais pas un octet complet
        {0, 0, 0, 0, 0, 0, 0, 0},                           // Octet de 0
        {1, 1, 1, 1, 1, 1, 1, 1},                           // Octet de 1
        {0, 1, 0, 1, 0, 1, 0, 1},                           // Motif alterné
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},   // Cas de plusieurs octets
        {0, 1, 0, 1, 0, 1, 0, 1, 1}                         // Cas avec un octet partiel
    };

    std::vector<std::vector<unsigned char>> expectedResults = {
        {},
        {0},
        {1},
        {5},
        {0},
        {255},
        {170},
        {170, 170},
        {170, 128}
    };

    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        std::vector<unsigned char> result = bitsToBytes(testCases[i]);
        if (result == expectedResults[i]) {
            std::cout << "Test case " << i << " passed." << std::endl;
        } else {
            std::cout << "Test case " << i << " failed." << std::endl;
            std::cout << "Input: ";
            for (bool bit : testCases[i]) { // boucle for pour chaque élément du tableau
                std::cout << bit; // Affiche les valeurs en binaire
            }           

            std::cout << std::endl;
            std::cout << "Expected: ";
            for (unsigned char byte : expectedResults[i]) { // boucle for pour chaque élément du tableau
                std::cout << std::hex << static_cast<int>(byte) << " "; // Affiche les valeurs en hexadécimal
            }
            std::cout << std::endl;
            std::cout << "Result: ";
            for (unsigned char byte : result) { // boucle for pour chaque élément du tableau
                std::cout << std::hex << static_cast<int>(byte) << " "; // Affiche les valeurs en hexadécimal
            }
            std::cout << std::endl;
        }
    }
}
