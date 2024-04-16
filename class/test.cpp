#include "BitArray.cpp"
#include "ByteArray.cpp"
#include "IntArray.cpp"
#include "Zeta.cpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;


int main(){

    cout << "----- BitArray -----" << endl;

    BitArray bitArray(8);
    // Set bit : 0 1 0 1 0 1 0 1
    bitArray.setBitArray({Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1), Bit(0), Bit(1)});
    cout << "Taille du tableau de bits : " << bitArray.getSize() << endl;
    cout << "Expected bit array : 01010101" << endl;
    cout << bitArray << endl << endl;

    cout << "----- BitsToBytes -----" << endl;
    // BitsToBytes
    ByteArray byteArray = ByteArray::bitsToBytes(bitArray);
    // Expected byte array : 0b01010101
    cout << "Taille du tableau de bytes : " << byteArray.getSize() << endl;
    cout << "Expected byte array : 0b01010101" << endl;
    cout << byteArray << endl << endl;

    cout << "----- BytesToBits -----" << endl;

    BitArray bitArray2 = BitArray::bytesToBits(byteArray);
    //Print bitArray2
    vector<Bit> bits = bitArray2.get();
    cout << bits.size() << endl;
    for (Bit bit : bits) {
        cout << bit.get();
    }

    cout << endl;
    cout << "----- Byte encode -----" << endl;

    IntArray F({15, 3});

    uint32_t d = 12;
    ByteArray oui = ByteArray::byteEncode(F, d);
    // Print oui
    vector<Byte> bytes2 = oui.get();
    cout << bytes2.size() << endl;
    // Print les bits avec bitset
    for (Byte byte : bytes2) {
        std::bitset<8> bits(byte.get());
        cout << bits << " ";
    }
    cout << endl;
    cout << "----- Byte decode -----" << endl;

    ByteArray singleBlock(8);
    singleBlock.set({0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b10101010, 0b01010101, 0b11111111, 0b00000000});
    
    std::vector<uint32_t> expectedSingle = {10, 5, 15, 0, 10, 5, 15, 0};
    IntArray singleResult = ByteArray::byteDecode(oui, d);
    // Print single result
    vector<uint16_t> results = singleResult.get();
    for (uint16_t result : results) {
        cout << result << " ";
    }

    return 0;
}