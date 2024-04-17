#pragma once

#include "BitArray.cpp"
#include "ByteArray.cpp"
#include "IntArray.cpp"
#include "NTT.cpp"
#include "Zeta.cpp"
#include "XOF.hpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;


void testNTTmatrice(){
    NTTCoef c0(0);
    NTTCoef c1(1);
    NTTCoef c2(2);
    NTTCoef c3(3);
    NTTCoef c4(4);
    NTTCoef c5(5);
    NTTCoef c6(6);
    NTTCoef c7(7);
    NTTCoef c8(8);
    
    NTT ntt1;
    ntt1.setCoef({c0, c1, c2, c3, c4, c5, c6, c7, c8});
    NTT ntt2;
    ntt2.setCoef({c8, c7, c6, c5, c4, c3, c2, c1, c0});
    NTT ntt3;
    ntt3.setCoef({c1, c1, c1, c1, c2, c2, c2, c2, c2});
    NTT ntt4;
    ntt4.setCoef({c3, c3, c3, c3, c4, c4, c4, c4, c4});
    NTT ntt5;
    ntt5.setCoef({c1, c1, c1, c1, c1, c1, c1, c1, c1});
    NTT ntt6;
    ntt6.setCoef({c2, c2, c2, c2, c2, c2, c2, c2, c2});

    NTTmatrice m1;
    m1.set(0,0,ntt5);
    m1.set(0,1,ntt5);
    m1.set(1,0,ntt5);
    m1.set(1,1,ntt5);

    NTTmatrice m2;
    m2.set(0,0,ntt6);
    m2.set(0,1,ntt6);
    m2.set(1,0,ntt6);
    m2.set(1,1,ntt6);

    cout << endl << "----- NTT matrice 1-----" << endl;
    for(int i=0; i<m1.sizeRow(); i++){
        for(int j=0; j<m1.sizeCol(); j++){
            cout << endl << "NTT matrice 1: " << i << " " << j << endl;
            for(int k=0; k<m1.get(i,j).getCoef().size(); k++){
                if(k<9){
                    cout << m1.get(i,j).getCoef()[k] << " ";
                }
            }
            cout << endl;
        }
    }

    cout << endl << "----- NTT matrice 2-----" << endl;
    for(int i=0; i<m2.sizeRow(); i++){
        for(int j=0; j<m2.sizeCol(); j++){
            cout << endl << "NTT matrice 2: " << i << " " << j << endl;
            for(int k=0; k<m2.get(i,j).getCoef().size(); k++){
                if(k<9){
                    cout << m2.get(i,j).getCoef()[k] << " ";
                }
            }
            cout << endl;
        }
    }

    NTTmatrice m3 = m1*m2;
    cout << endl << "----- NTT matrice 3 = m1*m2-----" << endl;
    for(int i=0; i<m3.sizeRow(); i++){
        for(int j=0; j<m3.sizeCol(); j++){
            cout << endl << "NTT matrice 3: " << i << " " << j << endl;
            for(int k=0; k<m3.get(i,j).getCoef().size(); k++){
                if(k<9){
                    cout << m3.get(i,j).getCoef()[k] << " ";
                }
            }
            cout << endl << endl;
        }
    }
}



int main(){

    /*cout << "----- BitArray -----" << endl;

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
    cout << decodeArray2 << endl << endl;*/

    testNTTmatrice();

    cout << "----- XOF -----" << endl;
    vector<uint8_t> rho = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    XOF xof(rho,2,2); xof.init();
    for(int i=0;i<xof.digest.size();i++) cout << static_cast<uint16_t>(xof.digest[i]) << " ";
    cout << endl; xof.next();
    for(int i=0;i<xof.digest.size();i++) cout << static_cast<uint16_t>(xof.digest[i]) << " ";
    cout << endl; xof.next();
    for(int i=0;i<xof.digest.size();i++) cout << static_cast<uint16_t>(xof.digest[i]) << " ";
    cout << endl << endl;

    return 0;
}