#include <cstdint>
#include <iostream>
#include <vector>
#include <cryptopp/shake.h>
#include "ByteArray.hpp"

using namespace std;

// TODO Test w/ ByteArrays
class XOF {

    private:

        // Attributes
        vector<uint8_t> inputData;
        int size;

    public:

        // Constructor
        XOF(vector<uint8_t>& rho, int i, int j);

        // Methods
        ByteArray init();

        ByteArray next();

        // Destructor
        ~XOF();

};

// Constructor

XOF::XOF(vector<uint8_t>& rho, int i, int j) {
    // Convert integers to byte arrays
    vector<uint8_t> iBytes(sizeof(uint32_t));
    vector<uint8_t> jBytes(sizeof(uint32_t));
    memcpy(iBytes.data(), &i, sizeof(uint32_t));
    memcpy(jBytes.data(), &j, sizeof(uint32_t));

    // Concatenate to make the input data
    this->inputData.insert(this->inputData.end(), rho.begin(), rho.end());
    this->inputData.insert(this->inputData.end(), iBytes.begin(), iBytes.end());
    this->inputData.insert(this->inputData.end(), jBytes.begin(), jBytes.end());
}

// Methods

ByteArray XOF::init() {
    CryptoPP::SHAKE128 shake(32);
    vector<uint8_t> digest(32);
    shake.Update(this->inputData.data(), this->inputData.size());
    shake.Final(digest.data());

    // Keep the size of the digest in memory
    this->size = digest.size();

    ByteArray result(digest.size());
    result.setVec(digest);
    return result;
}

ByteArray XOF::next() {
    CryptoPP::SHAKE128 shake(size+3);
    shake.Restart();
    vector<uint8_t> digest(size+3);
    this->size+=3;
    shake.Update(this->inputData.data(), inputData.size());
    shake.Final(digest.data());

    ByteArray result(digest.size());
    result.setVec(digest);
    return result;
}

//Destructor

XOF::~XOF() {
}