#ifndef BYTEDECODE_HPP
#define BYTEDECODE_HPP

#include <cstdint>
#include <vector>
#include "../headers/bytesToBits.hpp"

using namespace std;

vector<uint32_t> byteDecode(const vector<uint8_t>& B, uint32_t d);

void testByteDecode();

#endif