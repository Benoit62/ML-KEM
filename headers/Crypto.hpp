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
    static uint16_t compress(uint16_t y, uint16_t d);
    static uint16_t decompress(uint16_t x, uint16_t d);
};

#endif