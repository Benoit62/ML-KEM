#include "../headers/BitRev7.hpp"

uint32_t BitRev7(uint32_t x) {
    x = (x & 0x00000000ffffffffU) << 16 | (x & 0xffffffff00000000U) >> 16;
    x = (x & 0x0000ffff0000ffffU) << 8 | (x & 0xffff0000ffff0000U) >> 8;
    x = (x & 0x00ff00ff00ff00ffU) << 4 | (x & 0xff00ff00ff00ff00U) >> 4;
    x = (x & 0x0f0f0f0f0f0f0f0fU) << 2 | (x & 0xf0f0f0f0f0f0f0f0U) >> 2;
    x = (x & 0x3333333333333333U) << 1 | (x & 0xccccccccccccccccU) >> 1;
    return x;
}
