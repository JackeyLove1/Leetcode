#include <cstdio>
#include <iostream>
/*
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>
 */

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

constexpr int N = 50100, M = 20010, INF = 1e8;
int p[N], w[N];

double a, b, c, d;

inline double f(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    fhj();
    cin >> a >> b >> c >> d;
    int s = 0;
    for (int i = -100; i < 100; ++i) {
        double l = i + 0.0, r = i + 1.0;
        if (!f(l)){
            printf("%.2lf ", l);
            ++s;
        }
        if (f(l) * f(r) < 0) {
            while (r - l >= 0.01) {
                auto mid = (l + r) / 2;
                if (f(mid) * f(r) <= 0) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            printf("%.2lf ", r);
            ++s;
            if (s == 3) {
                break;
            }
        }
    }
    return 0;
}