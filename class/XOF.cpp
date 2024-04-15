#include <cstdint>
#include <iostream>
#include <vector>
#include <cryptopp/shake.h>

using namespace std;

class XOF {

    private:

    // Attributes
    CryptoPP::SHAKE128 shake;
    vector<uint8_t> inputData;
    int size;

    public:

    // Constructor
    XOF(vector<uint8_t>& rho, int i, int j) {
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

    vector<uint8_t> init() {
        vector<uint8_t> digest(shake.DigestSize());
        shake.Update(this->inputData.data(), this->inputData.size());
        shake.Final(digest.data());

        // Keep the size of the digest in memory
        this->size = digest.size();

        return digest;
    }

    // Methods
    vector<uint8_t> next() {
        shake.Restart();
        vector<uint8_t> digest(size+3);
        this->size+=3;
        shake.Update(this->inputData.data(), inputData.size());
        shake.Final(digest.data());

        return digest;
    }

    // Destructor
    ~XOF() {}

};