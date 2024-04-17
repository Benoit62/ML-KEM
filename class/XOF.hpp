#ifndef XOF_CPP
#define XOF_CPP

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
    public:
        vector<uint8_t> digest;
        // Constructor
        XOF(vector<uint8_t>& rho, int i, int j);
        // Methods
        void init();
        void next();
        // Destructor
        ~XOF();
};

#endif