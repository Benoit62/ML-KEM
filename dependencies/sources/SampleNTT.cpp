#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include "../headers/SampleNTT.hpp"

//Vecteur testés pour j < 9
// 0 0 0 0 0 0 0 0 0 -> 0 0 0 0 0 0 0 0 0  correct
// 1 0 0 1 0 0 1 0 0 -> 1 0 1 0 1 0 0 0 0 0 correct
// 1 0 1 1 0 1 1 0 1 -> 1 16 1 16 1 16 0 0 0 0 correct
// 255 15 255 255 15 255 255 15 255 -> 0 0 0 0 0 0 0 0 0 correct (le triplet a été choisit pour toujours etre skip)

// Principale probleme, si i depasse le nombre de valeur dans le vecteur d'entrée, la focntion va "inventé" des termes
// Exemple avec j < 256 et 255 15 255 255 15 255 255 15 255 en entrée :
// 0 0 0 0 0 0 0 0 0 0 1041 0 0 0 0 1632 102 1634 1568 1638 1568 1638 1568 518 1638 518 1638 518 102 1634 102 162 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 

uint32_t q = 3329; 
std::vector<uint32_t> SampleNTT(const std::vector<uint8_t>& B) {
    std::vector<uint32_t> a;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t d1, d2;

    while (j < 256) {
        d1 = B[i] + 256 * (B[i + 1] % 16);
        d2 = static_cast<int>(floor(B[i + 1] / 16.0)) + 16 * B[i + 2];

        if (d1 < q) {
            a.push_back(d1);
            j++;
        }

        if (d2 < q && j < 256) {
            a.push_back(d2);
            j++;
        }
        i += 3;
    }

    return a;
}

// Fonction de test pour SampleNTT
void testSampleNTT() {
    // Initialiser le générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));

    // Générer un vecteur de bytes aléatoires
    std::vector<unsigned char> randomBytes = generateRandomBytes(768);

    // Appeler SampleNTT
    std::vector<uint32_t> result = SampleNTT(randomBytes);

    // Vérifier la taille du résultat
    if (result.size() != 256) {
        std::cout << "Erreur : la taille du résultat n'est pas 256" << std::endl;
        return;
    }

    // Vérifier les valeurs du résultat
    for (uint32_t value : result) {
        if (value < 0 || value >= q) {
            std::cout << "Erreur : valeur invalide dans le résultat (" << value << ")" << std::endl;
            return;
        }
    }

    std::cout << "Test réussi !" << std::endl;
}

int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));

    // Input : Vecteur de bytes aléatoires
    std::vector<unsigned char> randomBytes = {
        255, 15, 255, 255, 15, 255, 255, 15, 255,
        // ... (768 bytes au total)
    };

    std::cout << "Input :" << std::endl;
    for (uint8_t byte : randomBytes) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;

    // Appel de SampleNTT
    std::vector<uint32_t> result = SampleNTT(randomBytes);



    std::cout << "Output :" << std::endl;
    for (uint32_t value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
