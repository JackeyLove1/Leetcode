#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2, MOD = 1e9 + 7;
using ll = long long;
ll temp[N][N];
ll n, k;

class Matrix {
public:
    ll m[N][N];
    size_t sz;

    Matrix(int sz_) : sz(sz_) { memset(m, 0, sizeof m); }

    Matrix() : sz(0) { memset(m, 0, sizeof m); }

    Matrix(const Matrix &other) : sz(other.sz) {
        if (&other == this) {
            return;
        }
        memcpy(m, other.m, sizeof other.m);
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
        for (int i = 0; i < matrix.sz; ++i) {
            for (int j = 0; j < matrix.sz; ++j) {
                os << matrix.m[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }


    Matrix &operator=(const Matrix &other) {
        if (&other == this) {
            return *this;
        }
        memcpy(m, other.m, sizeof other.m);
        sz = other.sz;
        return *this;
    }
};

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    assert(lhs.sz == rhs.sz);
    auto sz = lhs.sz;
    Matrix res(sz);
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            for (int k = 0; k < sz; ++k) {
                res.m[i][j] = (res.m[i][j] + lhs.m[i][k] * rhs.m[k][j]) % MOD;
            }
        }
    }
    return res;
}

inline Matrix qpow(Matrix &a, ll b) {
    Matrix res(a.sz);
    for (int i = 0; i < res.sz; ++i) res.m[i][i] = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    fhj();
    cin >> n;
    if (n <= 2) {
        cout << 1 << endl;
        return 0;
    }
    Matrix a(2);
    ll m1[2][2] = {{1, 1},
                   {1, 0}};
    memcpy(a.m, m1, sizeof m1);
    auto A = qpow(a, n - 2);
    Matrix b(2);
    ll m2[2][2] = {{1, 0},
                   {1, 0}};
    memcpy(b.m, m2, sizeof m2);
    auto res = A * b;
    cout << res.m[0][0] << endl;
    return 0;
}