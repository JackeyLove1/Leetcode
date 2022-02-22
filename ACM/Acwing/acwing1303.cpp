#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;
const int N = 3;
int n, m;

// 矩阵向量乘法
void mul(int c[], int a[], int b[][N]) { // 1 x m * m * n -> 1 x n
    int temp[N] = {0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp[i] = (temp[i] + (ll) a[j] * b[j][i] % m) % m;
        }
    }
    memcpy(c, temp, sizeof temp);
}

// 矩阵矩阵乘法
void mul(int c[][N], int a[][N], int b[][N]) {
    int temp[N][N] = {0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                temp[i][j] = (temp[i][j] + (ll) a[i][k] * b[k][j] % m) % m;
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
    --n;
    while (n) {
        if (n & 1) mul(f1, f1, a);
        mul(a, a, a);
        n >>= 1;
    }
    cout << f1[2] << endl;
    return 0;
}