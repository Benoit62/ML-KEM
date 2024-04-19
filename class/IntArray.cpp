#include "../headers/IntArray.hpp"

// Constructors
IntArray::IntArray() : data(MAX_SIZE, 0){}
IntArray::IntArray(int size) : data(size, 0) {}
IntArray::IntArray(const vector<uint16_t>& values) {
    if(values.size() > MAX_SIZE) { cout << "Input vector size exceeds limit."; }
    else { data=values; }
}

// Methods
void IntArray::set(uint16_t newValue, int index) { this->data[index] = newValue; }
uint16_t IntArray::get(int index) { return this->data[index]; }
vector<uint16_t> IntArray::get() { return this->data; }
size_t IntArray::getSize() { return this->data.size(); }

// Destructor
IntArray::~IntArray() {}

// Operators
ostream& operator<<(ostream& os, IntArray& intArr) {
    for(int i = 0; i < intArr.getSize(); i++) {
        os << intArr.get(i);
        if(i < intArr.getSize() - 1) {
            os << " ";
        }
    }
    return os;
}