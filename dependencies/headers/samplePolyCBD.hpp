#ifndef SAMPLEPOLYCBD_HPP
#define SAMPLEPOLYCBD_HPP

#include <vector>
#include <cstdint>
#include "../headers/bytesToBits.hpp"

using namespace std;

vector<uint32_t> SamplePolyCBD_eta(const vector<uint8_t>& B, uint32_t eta, uint32_t q);

void testSamplePolyCBD_eta();

#endif