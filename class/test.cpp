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
    cout << "Expected bit array : 0-1-0-1-0-1-0-1" << endl;
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
    // Expected bit array : 0-1-0-1-0-1-0-1
    cout << "Taille du tableau de bits : " << bitArray2.getSize() << endl;
    cout << "Expected bit array : 0-1-0-1-0-1-0-1" << endl;
    cout << bitArray2 << endl << endl;


    cout << "----- IntArray -----" << endl;
    IntArray F({15, 3});
    // Expected int array : 15 3
    cout << "Expected int array : 15 3" << endl;
    cout << F << endl << endl;


    cout << "----- Byte encode -----" << endl;
    uint32_t d = 12;
    ByteArray byteArray3 = ByteArray::byteEncode(F, d);
    // Expected byte array : 0b00001111 0b00000011
    cout << "Taille du tableau de bytes : " << byteArray3.getSize() << endl;
    cout << "Expected byte array : 00000000 11110000 00000011" << endl;
    cout << byteArray3 << endl << endl;


    cout << "----- Byte decode -----" << endl;

    ByteArray singleBlock(8);
    singleBlock.set({0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b00001111});
    cout << "Taille du tableau de bytes : " << singleBlock.getSize() << endl;
    cout << "Expected byte array : 10101010 01010101 11111111 00000000 10101010 01010101 11111111 00000000" << endl;
    cout << singleBlock << endl << endl;
    
    std::vector<uint32_t> expectedSingle = {10, 5, 15, 0, 10, 5, 15, 0};
    IntArray singleResult = ByteArray::byteDecode(byteArray3, d);
    cout << "Taille du tableau d'entiers : " << singleResult.getSize() << endl;
    cout << "Expected int array : 10 5 15 0 10 5 15 3840" << endl;
    cout << singleResult << endl << endl;
    

    cout << "----- IntArray -----" << endl;
    IntArray F2({15, 3, 2501, 0});
    // Expected int array : 15 3, 2501 0
    cout << "Expected int array : 15 3 2501 0" << endl;
    cout << F2 << endl << endl;


    cout << "----- Byte encode -----" << endl;
    ByteArray byteArray4 = ByteArray::byteEncode(F2, d);
    // Expected byte array : 0b00001111 0b00000011
    cout << "Taille du tableau de bytes : " << byteArray4.getSize() << endl;
    cout << "Expected byte array : 10101010 01010101 11111111 00000000 10101010 01010101 11111111 00000000" << endl;
    cout << byteArray4 << endl << endl;

    return 0;
}