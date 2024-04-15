#include "BitArray.cpp"
#include "ByteArray.cpp"

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

int main(){

    BitArray bitArray(8);
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
    }

    return 0;
}