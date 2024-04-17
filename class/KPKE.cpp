#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>
#include "ByteArray.hpp"
#include "IntArray.cpp"
#include "Crypto.cpp"
#include "constants.hpp"

using namespace std;

class KPKE {
    public:
    static pair<ByteArray, ByteArray> KeyGen();
    static ByteArray Encrypt(ByteArray ek_pke, ByteArray message, ByteArray r);
    static ByteArray Decrypt(ByteArray dk_pke, ByteArray c);
};

pair<ByteArray, ByteArray> KPKE::KeyGen() {
    ByteArray rho(32), sigma(32);
    pair<ByteArray, ByteArray> tmp  = Crypto::G(Crypto::generateRandomBytes(32));
    rho = tmp.first; sigma = tmp.second;
    uint16_t N=0;
    // TODO declare matrix here
    for(int i=0;i<k;i++) { for(int j=0;j<k;j++) {
        // fill A_hat matrix
    }}
}

ByteArray KPKE::Encrypt(ByteArray ek_pke, ByteArray message, ByteArray r) {
    uint16_t N=0;
    ByteArray e = ek_pke.split(0,384*k);
    IntArray t_hat = ByteArray::byteDecode(e, 12);
    ByteArray rho = ek_pke.split(384*k,384*k+32);
    // declare matrix here
    for(int i=0;i<k;i++) { for(int j=0;j<k;j++) {
        // fill A_hat matrix
    }}
}

ByteArray KPKE::Decrypt(ByteArray dk_pke, ByteArray c) {
    ByteArray c1 = c.split(0,32*du*k);
    ByteArray c2 = c.split(32*du*k,32*(du*k+dv));
    ByteArray u(c1.getSize());
    for(int i=0;i<c1.getSize();i++) { u.get()[i] = Crypto::decompress(ByteArray::byteDecode(c1, du).get()[i], du); }
    ByteArray v(c2.getSize());
    for(int i=0;i<c2.getSize();i++) { v.get()[i] = Crypto::decompress(ByteArray::byteDecode(c2, dv).get()[i], dv); }
    IntArray s_hat = ByteArray::byteDecode(dk_pke, 12);
}