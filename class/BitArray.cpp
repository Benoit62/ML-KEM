#include "../headers/BitArray.hpp"

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

vector<Bit> BitArray::get() {
    return this->bits;
}

int BitArray::getSize() {
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

ostream& operator<<(ostream& os, BitArray& b){
    for(int i = 0; i < b.getSize(); i++){
        os << b.get()[i].get() ? "1" : "0";
        if(i % 8 == 7){
            os << " ";
        }
        else {
            if(i < b.getSize() - 1){
                os << "-";
            }
        }
    }
    return os;
}

void BitArray::setBitIndex(int index, Bit bit){
    this->bits[index] = bit;
}

BitArray BitArray::bytesToBits(ByteArray& b){
    size_t l = b.getSize();
    BitArray bits(8 * l);

    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < 8; j++) {
            bits.setBitIndex(8 * i + j, b.get()[i].get() >> (7 - j) & 1); 
        }
    }

    return bits;
}
