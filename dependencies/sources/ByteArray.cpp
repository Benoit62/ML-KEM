#ifndef BYTEARRAY_CPP
#define BYTEARRAY_CPP

#include "Byte.cpp"
#include "BitArray.cpp"

#include <iostream>
#include <vector>

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
};

ByteArray::ByteArray(int size){
    /*if(size % 8 != 0){
        throw std::invalid_argument("Size must be a multiple of 8");
    }*/
    this->size = size;
    for(int i = 0; i < size; i++){
        Byte byte(0);
        this->bytes.push_back(byte);
    } 
}

ByteArray::~ByteArray(){
    // Destructor
}

vector<Byte> ByteArray::get(){
    return this->bytes;
}

size_t ByteArray::getSize(){
    return this->size;
}

void ByteArray::set(vector<Byte> byte){
    this->bytes = byte;
}

void ByteArray::add(uint16_t nb, int index){
    // Additionne le nombre à l'index
    this->bytes[index].set(this->bytes[index].get() + nb);
}

static ByteArray bitsToBytes(BitArray& b) {
    size_t l = b.getSize() / 8;
    ByteArray bytes(l);

    for (size_t i = 0; i < b.getSize(); i++) {
        size_t byteIndex = i / 8;
        size_t bitIndex = i % 8;
        bytes.add((b.get()[i].get() ? 1 << (7 - bitIndex) : 0), byteIndex);
    }

    return bytes;
}


#endif // BYTEARRAY_CPP
