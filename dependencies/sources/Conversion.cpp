#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <bitset>

typedef std::vector<uint8_t> bytesArray;
typedef std::vector<uint8_t> bitsArray;

class Conversion {

    private:
        const uint32_t q = 3329; // Valeur de q à enlever une fois que l'on aura un fichier avec les constantes        

    protected:


    public:
        Conversion(){}

        bytesArray bitsToBytes(const bitsArray& bits) {
            bytesArray bytes;
            uint8_t byte = 0;
            int bitIndex = 7; // LSB est à droite

            for (bool bit : bits) {
                byte |= static_cast<uint8_t>(bit) << bitIndex;
                bitIndex--;

                if (bitIndex < 0) {
                    bytes.push_back(byte);
                    byte = 0;
                    bitIndex = 7;
                }
            }

            if (bitIndex < 7) {
                bytes.push_back(byte);
            }

            return bytes;
        }

        bitsArray bytesToBits(const bytesArray& B) {
            bytesArray Bytes = B;
            size_t l = B.size();
            bitsArray b(8 * l);

            for (size_t i = 0; i < l; i++) {
                for (size_t j = 0; j < 8; j++) {
                    b[8 * i + j] = Bytes[i] % 2;
                    Bytes[i] = Bytes[i] / 2;
                }
                reverse(b.begin()+8*i, b.begin()+8*i+8);
            }
            return b;
        }

        bytesArray encodeBytes(const std::vector<uint8_t>& F, int d) {
            int m;
            if (d < 12) {
                m = (1 << d);
            } else {
                m = 4096;  // q = 2^12 pour d = 12
            }

            bitsArray b(F.size() * d, false);

            for (int i = 0; i < F.size(); i++) {
                uint16_t a = F[i];
                for (int j = 0; j < d; j++) {
                    b[i * d + (d - 1 - j)] = a % 2; // Modification pour que le bit de poids faible soit à droite
                    a = (a - b[i * d + (d - 1 - j)]) / 2;
                }
            }

            return bitsToBytes(b);
        }

        std::vector<uint32_t> byteDecode(const bytesArray& B, uint32_t d) {
            bitsArray bits = bytesToBits(B);
            uint32_t m = (d < 12) ? (1 << d) : 3329; // m = 2^d si d < 12, sinon m = 3329

            std::vector<uint32_t> F(256); // Tableau de taille 256

            for (int i = 0; i < 256; i++) { // Pour chaque élément de F
                uint32_t sum = 0;
                for (int j = 0; j < d; j++) {   // Pour chaque élément de d
                    sum += bits[i * d + j] * (1 << j); // On ajoute à sum le produit de l'élément de bits correspondant à l'élément de F et de d
                }
                F[i] = sum % m; // On ajoute à F la somme modulo m
            }
            return F;
        }

        // Fonction de compression
        uint32_t compress(uint32_t x, uint32_t d) {
            if (d >= 12) {
                // Erreur : d doit être strictement inférieur à 12
                return -1;
            }
            double factor = pow(2, d) / q;
            return static_cast<uint32_t>(floor(factor * x));
        }

        // Fonction de décompression
        uint32_t decompress(uint32_t y, uint32_t d) {
            if (d >= 12) {
                // Erreur : d doit être strictement inférieur à 12
                return -1;
            }
            double factor = q / pow(2, d);
            return static_cast<uint32_t>(floor(factor * y));
        }
};

int main(){
    Conversion conv;
    // Test bitsToBytes
    bitsArray b = {1,0,1,0,1,0,1,0};
    bitsArray bytes = conv.bitsToBytes(b);
    // Print bytes
    for (size_t i = 0; i < bytes.size(); i++) {
        std::bitset<8> bits(bytes[i]);
        std::cout << bits << " ";
    }

    // Test bytesToBits
    /*bytesArray singleByte = {0b10101010};
    bitsArray b = conv.bytesToBits(singleByte);
    bitsArray expectedSingleBits = {1,0,1,0,1,0,1,0};
    assert(b == expectedSingleBits); 


    // Test byteDecode
    bitsArray singleBlock = {0b10101010, 0b01010101, 0b11111111, 0b00000000,
                                   0b10101010, 0b01010101, 0b11111111, 0b00000000};
    uint32_t d = 4;
    std::vector<uint32_t> expectedSingle = {10, 5, 15, 0, 10, 5, 15, 0};
    std::vector<uint32_t> singleResult = conv.byteDecode(singleBlock, d);
    // Print expectedSingle
    /*for (size_t i = 0; i < expectedSingle.size(); i++) {
        std::cout << expectedSingle[i] << " ";
    }

    // Print singleResult
    for (size_t i = 0; i < singleResult.size(); i++) {
        std::cout << singleResult[i] << " ";
    }

    //assert(singleResult == expectedSingle);

    bytesArray oui = conv.encodeBytes({15,3}, 8);
    for (size_t i = 0; i < oui.size(); i++) {
        std::bitset<8> bits(oui[i]);
        std::cout << bits << " ";
    }*/
    

    
    

    
}
