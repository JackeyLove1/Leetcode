#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2200, M = 550;
using ll = long long;
int f[N][N];
constexpr int INF = 0x3f3f3f3f;
int n, m;
int a[N];

class Solution {
public:
    int minAreaRect(const vector<vector<int>> &points) {
        int res = INT_MAX;
        for (const auto &A : points) {
            for (const auto &B: points) {
                if (A == B) continue;
                for (const auto &C : points) {
                    if (A == C || B == C)continue;
                    for (const auto &D: points) {
                        if (A == D || B == D || C == D) continue;
                        if (A[1] == B[1] && D[1] == C[1] && A[0] == D[0] && B[0] == C[0]) {
                            res = min(abs(A[1] - D[1]) * abs(A[0] - B[0]), res);
                        }
                    }
                }
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};


