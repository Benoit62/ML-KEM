#pragma once

#include "Bit.cpp"

#include <iostream>
#include <vector>
#include <cstdint>

class ByteArray;

using namespace std;

class BitArray {
    private:
        vector<Bit> bits;
        int size;
    public:
        BitArray(int size);
        ~BitArray();
        vector<Bit> get();
        int getSize();
        void setBitArray(vector<Bit> bits);
        bool getIndex(int index);
        void reverse(int index);
        void addBit(Bit bit);
        void setBitIndex(int index, Bit bit);

        static BitArray bytesToBits(ByteArray& bytes){
            size_t l = bytes.getSize();
            BitArray bits(8 * l);

            for (size_t i = 0; i < l; i++) {
                for (size_t j = 0; j < 8; j++) {
                    bits.setBitIndex(8 * i + j, bytes.get()[i].get() >> (7 - j) & 1); 
                }
            }

            return bits;
        }

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, BitArray& b);
};
