#include <cstdint>
#include <utility>
#include <vector>
#include <cryptopp/sha3.h>
#include <cryptopp/shake.h>
#include "ByteArray.hpp"

using namespace std;

// TODO Test w/ ByteArrays
class Crypto {

    static pair<ByteArray, ByteArray> G(vector<uint8_t> c);

    static ByteArray H(ByteArray s);

    static ByteArray J(ByteArray s);

    static ByteArray PRF(ByteArray s, uint16_t b, uint16_t eta);

};

pair<ByteArray, ByteArray> Crypto::G(vector<uint8_t> c) {
    CryptoPP::SHA3_512 hash;
    vector<uint8_t> digest(hash.DigestSize());
    hash.Update(c.data(), c.size());
    hash.Final(digest.data());

    vector<uint8_t> rho(digest.begin(), digest.begin() + 32);
    vector<uint8_t> sigma(digest.begin() + 32, digest.end());

    ByteArray result1(rho.size());
    ByteArray result2(sigma.size());
    result1.setVec(rho);
    result2.setVec(sigma);

    return {result1, result2};
}

ByteArray Crypto::H(ByteArray s) {
    CryptoPP::SHA3_256 hash;
    vector<uint8_t> digest(hash.DigestSize());
    hash.Update(s.getVec().data(), s.getSize());
    hash.Final(digest.data());

    ByteArray result(digest.size());
    result.setVec(digest);
    return result;
}

ByteArray Crypto::J(ByteArray s) {
    CryptoPP::SHAKE256 shake;
    vector<uint8_t> digest(32);
    shake.Update(s.getVec().data(), s.getSize());
    shake.Final(digest.data());

    ByteArray result(digest.size());
    result.setVec(digest);
    return result;
}

ByteArray Crypto::PRF(ByteArray s, uint16_t b, uint16_t eta) {
    CryptoPP::SHAKE256 shake;

    vector<uint8_t> input(s.getVec().begin(), s.getVec().end());
    vector<uint8_t> bBytes(sizeof(uint32_t));
    memcpy(bBytes.data(), &b, sizeof(uint32_t));
    input.insert(input.end(), bBytes.begin(), bBytes.end());

    vector<uint8_t> digest(64 * eta);
    shake.Update(input.data(), input.size());
    shake.Final(digest.data());

    ByteArray result(digest.size());
    result.setVec(digest);
    return result;
}