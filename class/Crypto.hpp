#pragma once

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <cstdint>
#include <cmath>
#include <utility>
#include <random>
#include <vector>
#include <cryptopp/sha3.h>
#include <cryptopp/shake.h>
#include "ByteArray.hpp"

using namespace std;

class Crypto {
    public:
    static pair<ByteArray, ByteArray> G(vector<uint8_t> c);
    static ByteArray H(ByteArray s);
    static ByteArray J(ByteArray s);
    static ByteArray PRF(ByteArray s, uint16_t b, uint16_t eta);
    static vector<uint8_t> generateRandomBytes(uint32_t numBytes);
    static Byte compress(Byte y, uint16_t d);
    static Byte decompress(Byte x, uint16_t d);
};

#endif