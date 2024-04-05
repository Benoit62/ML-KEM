#ifndef MULTIPLY_NTT_HPP
#define MULTIPLY_NTT_HPP

// #include "../headers/baseCaseMultiply.hpp"
// #include "../headers/bitRev7.hpp"

#include <vector>
#include <cstdint>

using namespace std;

// Définition des constantes
// extern uint16_t q;
// extern uint32_t n;

vector<uint16_t> MultiplyNTTs(const vector<uint16_t>& fNTT, const vector<uint16_t>& gNTT);
void testMultiplyNTTs();

#endif // MULTIPLY_NTT_HPP

