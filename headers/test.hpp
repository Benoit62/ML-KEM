#ifndef TEST_HPP
#define TEST_HPP

#include "ByteArray.hpp"
#include "IntArray.hpp"
#include "BitArray.hpp"
#include "../class/NTT.cpp"
#include "../class/Zeta.cpp"
#include "../class/NTTmatrice.cpp"
#include "../class/PolyMatrice.cpp"
#include "XOF.hpp"
#include "Crypto.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

void testNTTmatrice();
void testBitByteArray();
void testXOF();
void testRBG();
void testCompDecomp();

#endif