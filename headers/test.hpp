#ifndef TEST_HPP
#define TEST_HPP

#include "ByteArray.hpp"
#include "IntArray.hpp"
#include "BitArray.hpp"
#include "NTT.hpp"
#include "Zeta.hpp"
#include "NTTmatrice.hpp"
#include "PolyMatrice.hpp"
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