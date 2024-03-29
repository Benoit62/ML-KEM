#include <iostream>
#include <vector>
#include <bitset>

std::vector<uint8_t> encodeBytes(const std::vector<uint32_t>& data, uint8_t d) {
    std::vector<uint8_t> encoded;
    uint32_t mask = (1 << d) - 1;
    uint32_t buffer = 0;
    uint8_t bitsRemaining = 0;

    for (size_t i = 0; i < 256; ++i) {
        uint32_t val = data[i] & mask;
        buffer = (buffer << d) | val;
        bitsRemaining += d;

        while (bitsRemaining >= 8) {
            encoded.push_back(static_cast<uint8_t>(buffer >> (bitsRemaining - 8)));
            bitsRemaining -= 8;
        }
    }

    if (bitsRemaining > 0) {
        encoded.push_back(static_cast<uint8_t>(buffer));
    }

    return encoded;
}

// Fonction pour afficher un vecteur de caractères non signés en hexadécimal
void print_vector(const std::vector<unsigned char>& v) {
    std::cout << "[ ";

    for (unsigned char c : v) {
        std::bitset<8> bits(c);
        std::cout << bits << " ";
    }

    std::cout << "]" << std::endl;
}

int testBytesEncode() {
    // Cas de test 1 : d = 8, F = {0, 1, 2, 3, ..., 255}
    std::vector<unsigned int> F1(256);
    for (unsigned int i = 0; i < 256; ++i) {
        F1[i] = i;
    }
    std::vector<unsigned char> encoded1 = encodeBytes(F1, 8);
    print_vector(encoded1);  // Affiche les octets encodés

    // Cas de test 2 : d = 5, F = {0, 1, 2, 3, ..., 31}
    std::vector<unsigned int> F2(32);
    for (unsigned int i = 0; i < 32; ++i) {
        F2[i] = i;
    }
    std::vector<unsigned char> encoded2 = encodeBytes(F2, 5);
    print_vector(encoded2);  // Affiche les octets encodés

    // Cas de test 3 : d = 12, F = {0, 1024, 2048, 3072, ..., 255 * 1024}
    std::vector<unsigned int> F3(256);
    for (unsigned int i = 0; i < 256; ++i) {
        F3[i] = i * 1024;
    }
    std::vector<unsigned char> encoded3 = encodeBytes(F3, 12);
    print_vector(encoded3);  // Affiche les octets encodés

    return 0;
}