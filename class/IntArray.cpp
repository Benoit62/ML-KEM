#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "../dependencies/headers/constants.hpp"

using namespace std;

class IntArray {

    private:
    
    // Attributes
    vector<uint16_t> data;
    static const int MAX_SIZE = n;

    public:

    // Constructors
    IntArray() : data(MAX_SIZE, 0) {}

    IntArray(const vector<uint16_t>& values) {
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

    // Destructor
    IntArray::~IntArray() {}
    
};