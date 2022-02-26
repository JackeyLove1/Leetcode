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

int A, B, C, D;
const int N = 45, M = 360;
int f[N][N][N][N];
int n, m;
int nums[M];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    }
    int x;
    while (m--) {
        cin >> x;
        if (x == 1) ++A;
        if (x == 2) ++B;
        if (x == 3) ++C;
        if (x == 4) ++D;
    }
    // f[0][0][0][0] = nums[1];
    for (int a = 0; a <= A; ++a) {
        for (int b = 0; b <= B; ++b) {
            for (int c = 0; c <= C; ++c) {
                for (int d = 0; d <= D; ++d) {
                    int pos =1 + a * 1 + b * 2 + c * 3 + d * 4;
                    int &v = f[a][b][c][d];
                    if (a != 0) v = max(v, f[a - 1][b][c][d]);
                    if (b != 0) v = max(v, f[a][b - 1][c][d]);
                    if (c != 0) v = max(v, f[a][b][c - 1][d]);
                    if (d != 0) v = max(v, f[a][b][c][d - 1]);
                    v += nums[pos];
                }
            }
        }
    }
    cout << f[A][B][C][D] << endl;
    return 0;
}