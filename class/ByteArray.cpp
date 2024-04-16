#include "ByteArray.hpp"
#include "BitArray.hpp"

#include <cmath>
#include <bitset>

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

vector<uint8_t> ByteArray::getVec() {
    vector<uint8_t> result;
    for(int i=0;i<this->bytes.size();i++) {
        result[i]=this->bytes[i].get();
    }
    return result;
}

ByteArray ByteArray::split(uint16_t start, uint16_t end) {
    vector<Byte> vec(this->bytes.begin()+start, this->bytes.begin()+end);
    ByteArray result(vec.size());
    result.set(vec);
    return result;
}

size_t ByteArray::getSize(){
    return this->size;
}

void ByteArray::set(vector<Byte> byte){
    this->bytes = byte;
}

void ByteArray::setVec(vector<uint8_t> vec) {
    for(int i=0;i<vec.size();i++) {
        this->bytes[i].set(vec[i]);
    }
}

void ByteArray::add(uint16_t nb, int index){
    // Additionne le nombre à l'index
    this->bytes[index].set(this->bytes[index].get() + nb);
}

ByteArray ByteArray::bitsToBytes(BitArray& b) {
    size_t l = b.getSize() / 8;
    ByteArray bytes(l);

    for (size_t i = 0; i < b.getSize(); i++) {
        size_t byteIndex = i / 8;
        size_t bitIndex = i % 8;
        bytes.add((b.get()[i].get() ? 1 << (7 - bitIndex) : 0), byteIndex);
    }

    return bytes;
}

ByteArray ByteArray::byteEncode(IntArray& F, uint32_t d) {
    BitArray b(F.getSize() * d);
    ByteArray B(F.getSize() * d);

    for (int i = 0; i < F.getSize(); i++) {
        uint32_t a = F.get(i);

        for (int j = 0; j < d; j++) {
            b.setBitIndex(i * d + j, (a >> (d - 1 - j)) & 1); // Mettre le bit de poids fort à gauche
        }
    }

    B = bitsToBytes(b);
    return B;
}

IntArray ByteArray::byteDecode(ByteArray& B, uint32_t d) {
    BitArray b = BitArray::bytesToBits(B);
    IntArray F(B.getSize()+1);

    for (int i = 0; i < B.getSize(); i++) {
        uint32_t sum = 0;

        for (int j = 0; j < d; j++) {
            sum += b.getIndex(i * d + j) * pow(2, d - 1 - j);
        }

        F.set(sum % (d < 12 ? 2 * d : static_cast<uint32_t>(pow(2, d))), i);
    }

    return F;
}

ostream& operator<<(ostream& os, ByteArray& b){
    for (Byte byte : b.get()) {
        std::bitset<8> bits(byte.get());
        os << bits << " ";
    }
    return os;
}
