#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>

using namespace std;

using ll = long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f;

int main() {
    for (int i = 0; i <= 1000; ++i) {
        for (int j = i + 1; j <= 1000; ++j) {
            for (int k = j + 1; k <= 1000; ++k) {
                if (i + j + k == 1000) {
                    if (std::pow(i, 2) + std::pow(j, 2) == std::pow(k, 2)) {
                        printf("%d^2 + %d^2 = %d^2", i, j, k);
                    }
                }
            }
        }
    }
}