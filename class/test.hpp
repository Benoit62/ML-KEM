#ifndef TEST_HPP
#define TEST_HPP

#include "ByteArray.hpp"
#include "IntArray.hpp"
#include "BitArray.hpp"
#include "NTT.cpp"
#include "Zeta.cpp"
#include "XOF.hpp"
#include "Crypto.hpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

void testNTTmatrice();
void testBitByteArray();
void testXOF();
void testRBG();
void testCompDecomp();

#endif