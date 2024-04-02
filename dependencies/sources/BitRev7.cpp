#include <iostream>
#include <vector>
#include <cstdint>

uint8_t BitRev7(uint8_t i) {
    i = ((i & 0x40) >> 6) | ((i & 0x20) >> 4) | ((i & 0x10) >> 2) | (i & 0x08) |
        ((i & 0x04) << 2) | ((i & 0x02) << 4) | ((i & 0x01) << 6);
    return i;
}

void testBitRev7() {
    std::vector<uint8_t> testCases = {0, 1, 42, 63, 64, 85, 127};
    std::vector<uint8_t> expectedResults = {0, 64, 42, 126, 1, 85, 127};

    for (size_t i = 0; i < testCases.size(); i++) {
        uint8_t result = BitRev7(testCases[i]);
        if (result == expectedResults[i]) {
            std::cout << "Test case " << i << " passed." << std::endl;
        } else {
            std::cout << "Test case " << i << " failed." << std::endl;
            std::cout << "Input: " << static_cast<int>(testCases[i]) << std::endl;
            std::cout << "Expected: " << static_cast<int>(expectedResults[i]) << std::endl;
            std::cout << "Result: " << static_cast<int>(result) << std::endl;
        }
    }
}