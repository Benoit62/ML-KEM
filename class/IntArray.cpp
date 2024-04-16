#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "constants.hpp"

using namespace std;

class IntArray {

    private:
    
        // Attributes
        vector<uint16_t> data;
        static const int MAX_SIZE = n;

    public:

        // Constructors
        IntArray();

        IntArray(int size);

        IntArray(const vector<uint16_t>& values);

        // Methods
        void set(uint16_t newValue, int index);
        
        uint16_t get(int index);

        vector<uint16_t> get();

        size_t getSize();

        // Destructor
        ~IntArray();

        friend ostream& operator<<(ostream& os, IntArray& intArr);
};

// Constructors

IntArray::IntArray() : data(MAX_SIZE, 0){
}

IntArray::IntArray(int size) : data(size, 0) {
}

IntArray::IntArray(const vector<uint16_t>& values) {
    if(values.size() > MAX_SIZE) { cout << "Input vector size exceeds limit."; }
    else { data=values; }
}

// Methods

void IntArray::set(uint16_t newValue, int index) {
    this->data[index] = newValue;
}

uint16_t IntArray::get(int index) {
    return this->data[index];
}

vector<uint16_t> IntArray::get() {
    return this->data;
}

size_t IntArray::getSize() {
    return this->data.size();
}

// Destructor

IntArray::~IntArray() {
}

ostream& operator<<(ostream& os, IntArray& intArr) {
    for(int i = 0; i < intArr.getSize(); i++) {
        os << intArr.get(i);
        if(i < intArr.getSize() - 1) {
            os << "-";
        }
    }
    return os;
}