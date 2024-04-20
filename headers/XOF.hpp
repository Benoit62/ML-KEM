#pragma once

#ifndef XOF_HPP
#define XOF_HPP

#include <cstdint>
#include <iostream>
#include <vector>
#include <cryptopp/shake.h>

using namespace std;

class XOF {
    private:
        // Attributes
        vector<uint8_t> inputData;
        int size;
        vector<uint8_t> digest;
    public:
        // Constructor
        XOF(vector<uint8_t>& rho, int i, int j);
        // Methods
        vector<uint8_t> getDigest();
        void init();
        void next();
        vector<uint8_t> getLastThree(int i);
        // Destructor
        ~XOF();
};

#endif