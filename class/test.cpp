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

    IntArray decodeArray = ByteArray::byteDecode(byteArray3, d);
    cout << "Taille du tableau d'entiers : " << decodeArray.getSize() << endl;
    cout << "Expected int array : 15 3" << endl;
    cout << decodeArray << endl << endl;


    cout << "----- Byte decode -----" << endl;

    ByteArray singleBlock(9);
    singleBlock.set({0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b10101010, 0b01010101, 0b11111111, 0b00000000, 0b00001111});
    cout << "Taille du tableau de bytes : " << singleBlock.getSize() << endl;
    cout << "Expected byte array : 10101010 01010101 11111111 00000000 10101010 01010101 11111111 00000000 00001111" << endl;
    cout << singleBlock << endl << endl;
    
    IntArray singleArray = ByteArray::byteDecode(singleBlock, 8);
    cout << "Taille du tableau d'entiers : " << singleArray.getSize() << endl;
    cout << "Expected int array : 10, 5, 15, 0, 10, 5, 15, 0, 15" << endl;
    cout << singleArray << endl << endl;
    
    

    cout << "----- IntArray -----" << endl;
    IntArray F2({2725, 1535, 10, 2645, 4080, 255});
    cout << "Expected int array : 2725, 1535, 10, 2645, 4080, 255" << endl;
    cout << F2 << endl << endl;


    cout << "----- Byte encode -----" << endl;
    ByteArray byteArray4 = ByteArray::byteEncode(F2, d);
    // Expected byte array : 0b00001111 0b00000011
    cout << "Taille du tableau de bytes : " << byteArray4.getSize() << endl;
    cout << "Expected byte array : 10101010 01010101 11111111 00000000 10101010 01010101 11111111 00000000 11111111" << endl;
    cout << byteArray4 << endl << endl;

    cout << "----- Byte decode -----" << endl;
    IntArray decodeArray2 = ByteArray::byteDecode(byteArray4, d);
    cout << "Taille du tableau d'entiers : " << decodeArray2.getSize() << endl;
    cout << "Expected int array : 2725, 1535, 10, 2645, 4080, 255" << endl;
    cout << decodeArray2 << endl << endl;

    return 0;
}