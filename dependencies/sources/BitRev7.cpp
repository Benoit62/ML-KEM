#include "../headers/BitRev7.hpp"

uint8_t BitRev7(uint8_t i) {
    i = ((i & 0x40) >> 6) | ((i & 0x20) >> 4) | ((i & 0x10) >> 2) | (i & 0x08) |
        ((i & 0x04) << 2) | ((i & 0x02) << 4) | ((i & 0x01) << 6);
    return i;
}