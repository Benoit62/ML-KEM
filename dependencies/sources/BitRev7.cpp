#include "../headers/BitRev7.hpp"

/*uint32_t BitRev7(uint32_t x) {
    x = (x & 0x00000000ffffffffU) << 16 | (x & 0xffffffff00000000U) >> 16;
    x = (x & 0x0000ffff0000ffffU) << 8 | (x & 0xffff0000ffff0000U) >> 8;
    x = (x & 0x00ff00ff00ff00ffU) << 4 | (x & 0xff00ff00ff00ff00U) >> 4;
    x = (x & 0x0f0f0f0f0f0f0f0fU) << 2 | (x & 0xf0f0f0f0f0f0f0f0U) >> 2;
    x = (x & 0x3333333333333333U) << 1 | (x & 0xccccccccccccccccU) >> 1;
    return x;
}*/

uint8_t BitRev7(uint8_t n) {
    if (n >> 7 != 0) {
        // Handle error condition (e.g., throw an exception)
        //throw std::runtime_error("not 7 bits");
    }

    uint8_t r = 0;
    r |= (n >> 6) & 0b00000001;
    r |= (n >> 4) & 0b00000010;
    r |= (n >> 2) & 0b00000100;
    r |= (n     ) & 0b00001000;
    r |= (n << 2) & 0b00010000;
    r |= (n << 4) & 0b00100000;
    r |= (n << 6) & 0b01000000;

    return r;
}
