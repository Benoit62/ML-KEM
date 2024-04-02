#ifndef NTT_HPP
#define NTT_HPP

#include "../sources/ntt.cpp"

void computeNTT(std::vector<int>& f, int q);

uint8_t BitRev7(uint8_t i);

void testComputeNTT();

#endif // NTT_HPP
