#pragma once

#ifndef INTARRAY_HPP
#define INTARRAY_HPP

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
        // Operators
        friend ostream& operator<<(ostream& os, IntArray& intArr);
};

#endif