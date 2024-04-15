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


ByteArray byteEncode(IntArray& F, uint32_t d) {
    BitArray b(F.getSize() * d);
    ByteArray B(F.getSize() * d);

    for (int i = 0; i < F.getSize(); i++) {
        uint32_t a = F.get(i);

        for (int j = 0; j < d; j++) {
            b.setBitIndex(i * d + j, (a >> (d - 1 - j)) & 1); // Mettre le bit de poids fort à gauche
        }
    }

    B = bitsToBytes(b);
    return B;
}

IntArray byteDecode(ByteArray& B, uint32_t d) {
    BitArray b = bytesToBits(B);
    IntArray F(B.getSize()*d);

    for (int i = 0; i < B.getSize(); i++) {
        uint32_t sum = 0;

        for (int j = 0; j < d; j++) {
            sum += b.getIndex(i * d + j) * pow(2, d - 1 - j);
        }

        F.set(sum % (d < 12 ? 2 * d : static_cast<uint32_t>(pow(2, d))), i);
    }

    return F;
}



int main(){

    cout << "----- BitArray -----" << endl;

    BitArray bitArray(8);
    // Set bit : 0 1 0 1 0 1 0 1
    bitArray.setBitArray({Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1)});
    // BitsToBytes
    ByteArray byteArray = ByteArray::bitsToBytes(bitArray);
    // Expected byte array : 0b01010101
    
    // Print byteArray byteArray
    vector<Byte> bytes = byteArray.get();
    cout << bytes.size() << endl;
    // Print les bits avec bitset
    for (Byte byte : bytes) {
        std::bitset<8> bits(byte.get());
        cout << bits << " ";
    }

    cout << endl;
    cout << "----- BytesToBits -----" << endl;

    BitArray bitArray2 = bytesToBits(byteArray);
    //Print bitArray2
    vector<Bit> bits = bitArray2.get();
    cout << bits.size() << endl;
    for (Bit bit : bits) {
        cout << bit.get();
    }

    cout << endl;
    cout << "----- Byte encode -----" << endl;

    /*IntArray F({15, 3});

    ByteArray oui = byteEncode(F, 8);
    // Print oui
    vector<Byte> bytes = oui.get();
    cout << bytes.size() << endl;
    // Print les bits avec bitset
    for (Byte byte : bytes) {
        std::bitset<8> bits(byte.get());
        cout << bits << " ";
    }
    cout << endl;
    cout << "----- Byte decode -----" << endl;

    ByteArray singleBlock(8);
    singleBlock.set({0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b10101010, 0b01010101, 0b11111111, 0b00000000});
    
    uint32_t d = 8;
    std::vector<uint32_t> expectedSingle = {10, 5, 15, 0, 10, 5, 15, 0};
    IntArray singleResult = byteDecode(oui, d);
    // Print single result
    vector<uint16_t> results = singleResult.get();
    for (uint16_t result : results) {
        cout << result << " ";
    }*/

    return 0;
}