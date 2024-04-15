#include "BitArray.hpp"
#include "ByteArray.hpp"

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
    }
    return os;
}

void BitArray::setBitIndex(int index, Bit bit){
    this->bits[index] = bit;
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
