#include "../dependencies/headers/BitArray.hpp"
#include "../dependencies/headers/Bit.hpp"

class BitArray {
    private:
        vector<Bit> bits;
        int size;
    public:
        BitArray(int size);
        ~BitArray();
        void set(int index, bool value);
        bool get(int index);
        void reverse(int index);
};

BitArray::BitArray(int size){
    this->size = size;
    this->bits = new Bit[size];
}