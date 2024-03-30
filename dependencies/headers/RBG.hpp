#ifndef RBG_HPP
#define RBG_HPP

#include <cstdint>
#include <vector>
#include "../sources/RBG.cpp"

using namespace std;

// Function to generate random bytes using an approved RBG
vector<uint8_t> generateRandomBytes(size_t numBytes);

#endif