#pragma once

#include "Byte.cpp"

#include <iostream>
#include <vector>
#include <cstdint>

class BitArray;

using namespace std;

class ByteArray {
    private:
        vector<Byte> bytes;
        int size;
    public:
        ByteArray(int size);
        ~ByteArray();
        vector<Byte> get();
        size_t getSize();
        void set(vector<Byte> byte);
        void add(uint16_t nb, int index);

        static ByteArray bitsToBytes(BitArray& b);

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, ByteArray& b);
};
