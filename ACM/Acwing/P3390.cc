#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 110, MOD = 1e9 + 7;
using ll = long long;
int n, temp[N][N];
ll k;
class Matrix {
public:
    ll m[N][N];

    Matrix() { memset(m, 0, sizeof m); }

    Matrix(const Matrix &other) {
        if (&other == this) {
            return;
        }
        memcpy(m, other.m, sizeof other.m);
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
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
        return *this;
    }
};

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    Matrix res{};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                res.m[i][j] = (res.m[i][j] + lhs.m[i][k] * rhs.m[k][j]) % MOD;
            }
        }
    }
    return res;
}

inline Matrix qpow(Matrix &a, ll b) {
    Matrix res{};
    for (int i = 0; i < n; ++i) res.m[i][i] = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    cin >> n >> k;
    Matrix a{};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a.m[i][j];
        }
    }
    auto res = qpow(a, k);
    cout << res;
    return 0;
}