#pragma once

#ifndef BYTEARRAY_HPP
#define BYTEARRAY_HPP

#include "Byte.hpp"
#include "BitArray.hpp"
#include "IntArray.hpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <bitset>

class BitArray;

using namespace std;

class ByteArray {
    private:
        vector<Byte> bytes;
        int size;
    public:
        ByteArray(int size);
        ByteArray(int size, uint8_t d);
        ~ByteArray();
        vector<Byte> get();
        size_t getSize();
        vector<uint8_t> getVec();
        ByteArray split(uint16_t start, uint16_t end);
        void set(vector<Byte> byte);
        void setVec(vector<uint8_t> byte);
        void add(uint16_t nb, int index);

        static ByteArray bitsToBytes(BitArray& b);
        static ByteArray byteEncode(IntArray& F, uint8_t d);
        static IntArray byteDecode(ByteArray& B, uint8_t d);

        // Déclaration de la surcharge de l'opérateur <<
        friend ostream& operator<<(ostream& os, ByteArray& b);
};

#endif