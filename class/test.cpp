#include "BitArray.cpp"
#include "ByteArray.cpp"
#include "IntArray.cpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <bitset>

using namespace std;

ByteArray bitsToBytes(BitArray& b) {
    size_t l = b.getSize() / 8;
    ByteArray bytes(l);

    for (size_t i = 0; i < b.getSize(); i++) {
        size_t byteIndex = i / 8;
        size_t bitIndex = i % 8;
        bytes.add((b.get()[i].get() ? 1 << (7 - bitIndex) : 0), byteIndex);
    }

    return bytes;
}

BitArray bytesToBits(ByteArray& bytes) {
    size_t l = bytes.getSize();
    BitArray bits(8 * l);

    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < 8; j++) {
            bits.setBitIndex(8 * i + j, bytes.get()[i].get() >> (7 - j) & 1); 
        }
    }

    return bits;
}


ByteArray encodeBytes(IntArray& F, int d) {
    int m;
    if (d < 12) {
        m = (1 << d);
    } else {
        m = 4096;  // q = 2^12 pour d = 12
    }

    BitArray b(F.getSize() * d);

    for (int i = 0; i < F.getSize(); i++) {
        uint16_t a = F.get(i);
        for (int j = 0; j < d; j++) {
            b.get()[i * d + (d - 1 - j)] = a % 2; // Modification pour que le bit de poids faible soit à droite
            a = (a - b.get()[i * d + (d - 1 - j)].get()) / 2;
        }
    }

    //Print b
    vector<Bit> bits = b.get();
    cout << bits.size() << endl;
    for (Bit bit : bits) {
        cout << bit.get();
    }

    return bitsToBytes(b);
}

/*std::vector<uint32_t> byteDecode(const bytesArray& B, uint32_t d) {
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
}*/


int main(){

    /*BitArray bitArray(8);
    // Set bit : 0 1 0 1 0 1 0 1
    bitArray.setBitArray({Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1)});
    // BitsToBytes
    ByteArray byteArray = bitsToBytes(bitArray);
    // Expected byte array : 0b01010101
    
    // Print byteArray byteArray
    vector<Byte> bytes = byteArray.get();
    cout << bytes.size() << endl;

    BitArray bitArray2 = bytesToBits(byteArray);
    //Print bitArray2
    vector<Bit> bits = bitArray2.get();
    cout << bits.size() << endl;
    for (Bit bit : bits) {
        cout << bit.get();
    }*/

    IntArray F({15, 3});

    ByteArray oui = encodeBytes(F, 8);
    // Print oui
    vector<Byte> bytes = oui.get();
    cout << bytes.size() << endl;
    for (Byte byte : bytes) {
        cout << byte.get() << endl;
    }

    return 0;
}