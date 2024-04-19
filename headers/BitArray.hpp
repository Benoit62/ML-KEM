#pragma once

#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include "Bit.hpp"
#include "ByteArray.hpp"

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

        static BitArray bytesToBits(ByteArray& b);

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, BitArray& b);
};

#endif