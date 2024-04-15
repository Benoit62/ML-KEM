#pragma once

#ifndef BITARRAY_CPP
#define BITARRAY_CPP

#include "Bit.cpp"

#include <iostream>
#include <vector>
#include <stdexcept>

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
        //static BitArray bytesToBits(ByteArray bytes);
};

BitArray::BitArray(int size){
    if(size % 8 != 0){
        throw std::invalid_argument("Size must be a multiple of 8");
    }
    this->size = size;
    for(int i = 0; i < size; i++){
        Bit bit(false);
        this->bits.push_back(bit);
    } 
}

BitArray::~BitArray(){
    // Destructor
}

vector<Bit> BitArray::get(){
    return this->bits;
}

int BitArray::getSize(){
    return this->size;
}

void BitArray::setBitArray(vector<Bit> bits){
    this->bits = bits;
}

bool BitArray::getIndex(int index){
    return this->bits[index].get();
}

void BitArray::reverse(int index){
    this->bits[index].reverse();
}

void BitArray::addBit(Bit bit){
    this->bits.push_back(bit);
}

/*static BitArray BitArray::bytesToBits(ByteArray bytes){
    size_t l = bytes.size();
    BitArray b(8 * l);

    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < 8; j++) {
            b[8 * i + j] = bytes[i] % 2;
            bytes[i] = bytes[i] / 2;
        }
        reverse(b.begin()+8*i, b.begin()+8*i+8);
    }
    return b;
}*/

void BitArray::setBitIndex(int index, Bit bit){
    this->bits[index] = bit;
}

#endif // BITARRAY_CPP