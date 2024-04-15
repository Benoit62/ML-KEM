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

        static BitArray bytesToBits(ByteArray& bytes);

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, BitArray& b);
};
