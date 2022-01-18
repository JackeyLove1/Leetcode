#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}


constexpr int N = 220;
const double INF = 999999;
double g[N][N], maxStep[N];
int n, m;
using PII = pair<int, int>;
PII p[N];

void floyed() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if(g[i][k] < INF && g[k][j] < INF){
                    g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
                }
            }
        }
    }
}

inline double getLength(const PII &p1, const PII &p2) {
    return sqrt(pow(p1.first - p2.first, 2)
                + pow(p1.second - p2.second, 2));
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    char x;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> x;
            if (x - '0') {
                g[i][j] = getLength(p[i], p[j]);
            } else {
                g[i][j] = INF;
            }
        }
    }
    floyed();
    double res1 = 0, res2 = INF;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] < INF) {
                maxStep[i] = max(maxStep[i], g[i][j]);
            }
        }
        res1 = max(res1, maxStep[i]);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(g[i][j] == INF){
                res2 = min(maxStep[i] + getLength(p[i], p[j]) + maxStep[j], res2);
            }
        }
    }
    auto res = max(res1, res2);
    printf("%.6lf\n", res);
    return 0;
}