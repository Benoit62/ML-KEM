#ifndef KPKE_KEYGEN_HPP
#define KPEK_KEYGEN_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include "../headers/RBG.hpp"
#include "../headers/samplePolyCBD.hpp"
#include "../headers/SampleNTT.hpp"
#include "../headers/bytesEncode.hpp"
#include "../headers/ntt.hpp"
#include "../headers/cryptoFunc.hpp"

using namespace std;

pair<vector<uint8_t>, vector<uint8_t>> KPKE_KeyGen();

#endif