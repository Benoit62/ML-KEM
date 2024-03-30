#ifndef CRYPTOFUNC_HPP
#define CRYPTOFUNC_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <cryptopp/sha3.h>
#include <cryptopp/shake.h>
#include "../sources/cryptoFunc.cpp"

using namespace std;

pair<vector<uint8_t>, vector<uint8_t>> G(vector<uint8_t> c);

vector<uint8_t> XOF(vector<uint8_t> rho, int i, int j);

vector<uint8_t> PRF(vector<uint8_t> s, int b, int eta);

#endif