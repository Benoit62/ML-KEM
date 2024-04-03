#ifndef NTT_HPP
#define NTT_HPP
#include <vector>
#include "BitRev7.hpp"

void computeNTT(std::vector<int>& f, int q, int n, int* roots);
void testComputeNTT();

#endif // NTT_HPP
