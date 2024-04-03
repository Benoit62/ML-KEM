// #include <cstdint>
#include <random>
#include "../headers/RBG.hpp"

using namespace std;

// Function to generate random bytes using an approved RBG
vector<uint8_t> generateRandomBytes(size_t numBytes) {
    // Create a seed sequence using a true random source (e.g., /dev/urandom on Unix-like systems)
    random_device rd;

    // Create a random engine using the seed sequence
    mt19937_64 engine(rd());

    // Create a uniform distribution for generating random bytes
    uniform_int_distribution<uint8_t> dist(0, numeric_limits<uint8_t>::max());

    // Generate and store the random bytes
    vector<uint8_t> randomBytes(numBytes);
    for (size_t i = 0; i < numBytes; i++) {
        randomBytes[i] = dist(engine);
    }
    return randomBytes;
}