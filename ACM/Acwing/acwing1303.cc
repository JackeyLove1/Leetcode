#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>

using namespace std;
using ull = __int128;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 3;

int n, m;

inline void mul(int c[], int a[], int b[][N]) {
    int temp[N] = {0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp[i] = (temp[i] + (ll)a[j] * b[j][i]) % m;
        }
    }
    memcpy(c, temp, sizeof temp);
}

inline void mul(int c[][N], int a[][N], int b[][N]) {
    int temp[N][N] = {0};
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            for (int k = 0; k < N; ++k){
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j] % m) % m;
            }
        }
    }
    memcpy(c, temp, sizeof temp);
}


int main() {
    fhj();
    cin >> n >> m;
    int f1[N] = {1, 1, 1};
    int a[N][N] = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 1}
    };
    n--;

    while (n) {
        if (n & 1) mul(f1, f1, a);
        mul(a, a, a);
        n >>= 1;
    }
    cout << f1[2] << endl;
    return 0;
}