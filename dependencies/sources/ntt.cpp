#include <iostream>
#include <vector>
#include <cassert>
#include "../headers/ntt.hpp"
#include "../headers/BitRev7.hpp"

using namespace std;

template<class T>
T extgcd(T a, T b, T& x, T& y) {
    for (T u = y = 1, v = x = 0; a;) {
        T q = b / a;
        swap(x -= q * u, u);
        swap(y -= q * v, v);
        swap(b -= q * a, a);
    }
    return b;
}

template<class T>
T mod_inv(T a, T m) {
    T x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}

ll mod_pow(ll a, ll n, ll mod) {
    ll ret = 1;
    ll p = a % mod;
    while (n) {
        if (n & 1) ret = ret * p % mod;
        p = p * p % mod;
        n >>= 1;
    }
    return ret;
}

void _ntt(vector<ll>& a, int sign) {
    const int n = a.size();
    assert((n ^ (n & -n)) == 0); // n = 2^k

    const int g = 3; // g is primitive root of mod
    int h = (int)mod_pow(g, (q - 1) / n, q); // h^n = 1
    if (sign == -1) h = (int)mod_inv<int>(h, q); // h = h^-1 % q

    // bit reverse
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }

    for (int m = 1; m < n; m *= 2) {
        const int m2 = 2 * m;
        const ll base = mod_pow(h, n / m2, q);
        ll w = 1;
        for (int x = 0; x < m; x++) {
            for (int s = x; s < n; s += m2) {
                ll u = a[s];
                ll d = a[s + m] * w % q;
                a[s] = u + d;
                if (a[s] >= q) a[s] -= q;
                a[s + m] = u - d;
                if (a[s + m] < 0) a[s + m] += q;
            }
            w = w * base % q;
        }
    }

    for (auto& x : a) if (x < 0) x += q;
}

vector<ll> ntt(const vector<ll>& f, int sign) {
    vector<ll> a = f;
    _ntt(a, sign);
    return a;
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
    int ntt_size = 1;
    while (ntt_size < a.size() + b.size()) ntt_size *= 2;

    vector<ll> _a = a, _b = b;
    _a.resize(ntt_size, 0);
    _b.resize(ntt_size, 0);

    auto a_ntt = ntt(_a, 1);
    auto b_ntt = ntt(_b, 1);

    vector<ll> c(ntt_size);
    for (int i = 0; i < ntt_size; i++) {
        c[i] = a_ntt[i] * b_ntt[i] % q;
    }

    return ntt(c, -1);
}
