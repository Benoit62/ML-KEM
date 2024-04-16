#pragma once

#include "Byte.cpp"
#include "IntArray.cpp"

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
        vector<uint8_t> getVec();
        void set(vector<Byte> byte);
        void setVec(vector<uint8_t> byte);
        void add(uint16_t nb, int index);

        static ByteArray bitsToBytes(BitArray& b);
        static ByteArray byteEncode(IntArray& F, uint32_t d);
        static IntArray byteDecode(ByteArray& B, uint32_t d);

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, ByteArray& b);
};
