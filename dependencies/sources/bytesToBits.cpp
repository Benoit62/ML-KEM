#include <vector>
using namespace std;

vector<bool> bytesToBits(const vector<unsigned char>& B) {
    size_t l = B.size();
    vector<bool> b(8 * l);

    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < 8; j++) {
            b[8 * i + j] = (B[i] & (1 << j)) != 0;
        }
    }
    return b;
}