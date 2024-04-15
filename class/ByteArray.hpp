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

        static ByteArray bitsToBytes(BitArray& b){
            size_t l = b.getSize() / 8;
            ByteArray bytes(l);

            for (size_t i = 0; i < b.getSize(); i++) {
                size_t byteIndex = i / 8;
                size_t bitIndex = i % 8;
                bytes.add((b.get()[i].get() ? 1 << (7 - bitIndex) : 0), byteIndex);
            }

            return bytes;
        }

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, ByteArray& b);
};
