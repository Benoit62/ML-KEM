#ifndef RBG_HPP
#define RBG_HPP

#include <cstdint>
#include <vector>

using namespace std;

// Function to generate random bytes using an approved RBG
vector<uint8_t> generateRandomBytes(uint32_t numBytes);

void testRandom(uint32_t test);

#endif