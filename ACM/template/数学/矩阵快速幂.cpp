/*
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
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 3;

int n, m;

// 类似于快速幂的写法
void mul(int c[], int a[], int b[][N]) // c <- a * b
{
    int temp[N] = {0};
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            temp[i] = (temp[i] + (LL)a[j] * b[j][i]) % m;

    memcpy(c, temp, sizeof temp);
}

void mul(int c[][N], int a[][N], int b[][N]) // c <- a * b
{
    int temp[N][N] = {0};
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            for (int k = 0; k < N; k ++ )
                temp[i][j] = (temp[i][j] + (LL)a[i][k] * b[k][j]) % m;

    memcpy(c, temp, sizeof temp);
}

int main()
{
    cin >> n >> m;

    int f1[N] = {1, 1, 1};
    int a[N][N] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1}
    };

    n -- ;
    while (n)
    {
        if (n & 1) mul(f1, f1, a);  // res = res * a
        mul(a, a, a);  // a = a * a
        n >>= 1;
    }

    cout << f1[2] << endl;

    return 0;
}
