#include <iostream>
#include "../headers/samplePolyCBD.hpp"

using namespace std;

vector<uint32_t> SamplePolyCBD_eta(const vector<uint8_t>& B, uint32_t eta, uint32_t q) {
    vector<bool> b = bytesToBits(B);
    vector<uint32_t> f(256);

    for (int i = 0; i < 256; i++) {
        uint32_t x = 0;
        uint32_t y = 0;

        for (int j = 0; j < eta; j++) {
            x += b[2 * i * eta + j];
            y += b[2 * i * eta + eta + j];
        }

        f[i] = (x - y + q) % q;
    }
    return f;
}

// Passe pas le test
void testSamplePolyCBD_eta() {
    vector<uint8_t> B = {0, 1, 0, 1}; // Example input data
    uint32_t eta = 2;
    uint32_t q = 3329;
    vector<uint32_t> expected_output = {3, 1, 3, 1}; // Expected output corresponding to the input data

    // Call the function
    vector<uint32_t> result = SamplePolyCBD_eta(B, eta, q);
    for(uint32_t elem : result) cout << elem << " ";
    cout << endl;

    // Compare the result with expected output
    if (result == expected_output) {
        cout << "Test Passed!" << endl;
    } else {
        cerr << "Test Failed!" << endl;
    }
}