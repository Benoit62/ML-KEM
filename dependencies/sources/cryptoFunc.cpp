#include "../headers/cryptoFunc.hpp"

using namespace std;

pair<vector<uint8_t>, vector<uint8_t>> G(vector<uint8_t> c) {
    // Compute SHA3-512 of c
    CryptoPP::SHA3_512 hash;
    vector<uint8_t> digest(hash.DigestSize());
    hash.Update(c.data(), c.size());
    hash.Final(digest.data());

    // Split digest into 2 seeds
    vector<uint8_t> rho(digest.begin(), digest.begin() + 32);
    vector<uint8_t> sigma(digest.begin() + 32, digest.end());

    return {rho, sigma};
}

vector<uint8_t> H(vector<uint8_t> s) {
    CryptoPP::SHA3_256 hash;
    vector<uint8_t> digest(hash.DigestSize());
    hash.Update(s.data(), s.size());
    hash.Final(digest.data());

    return digest;
}

vector<uint8_t> J(vector<uint8_t> s) {
    CryptoPP::SHAKE256 shake;
    vector<uint8_t> digest(32);
    shake.Update(s.data(), s.size());
    shake.Final(digest.data());

    return digest;
}

vector<uint8_t> XOF(vector<uint8_t> rho, int i, int j) {
    CryptoPP::SHAKE128 shake;

    // Convert integers to byte arrays
    vector<uint8_t> iBytes(sizeof(uint32_t));
    vector<uint8_t> jBytes(sizeof(uint32_t));
    memcpy(iBytes.data(), &i, sizeof(uint32_t));
    memcpy(jBytes.data(), &j, sizeof(uint32_t));

    // Concatenate the input data
    vector<uint8_t> inputData;
    inputData.insert(inputData.end(), rho.begin(), rho.end());
    inputData.insert(inputData.end(), iBytes.begin(), iBytes.end());
    inputData.insert(inputData.end(), jBytes.begin(), jBytes.end());

    // Compute the SHAKE128 of the input data
    vector<uint8_t> digest(32);
    shake.Update(inputData.data(), inputData.size());
    shake.Final(digest.data());

    return digest;
}

vector<uint8_t> PRF(vector<uint8_t> s, int b, int eta) {
    // Create a SHAKE256 object
    CryptoPP::SHAKE256 shake;

    // Concatenate s and b
    vector<uint8_t> input(s.begin(), s.end());
    vector<uint8_t> bBytes(sizeof(uint32_t));
    memcpy(bBytes.data(), &b, sizeof(uint32_t));
    input.insert(input.end(), bBytes.begin(), bBytes.end());

    // Compute SHAKE256(s||b, 64 * eta)
    vector<uint8_t> digest(64 * eta);
    shake.Update(input.data(), input.size());
    shake.Final(digest.data());

    return digest;
}