// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 110;
struct good {
    int p, c;
    double w;
} g[N];
int f[5100];
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> g[i].p >> g[i].c;
        g[i].w = 1.0 * g[i].p / g[i].c;
    }
    sort(g, g + n, [](good &g1, good &g2) {
       return g1.w > g2.w;
    });
    int w = (m/g[0].p + 1) *g[0].c;
    for (int i = 0; i < n; ++i) {
        for(int j = g[i].c; j <= w; ++j){
            f[j] = max(f[j], f[j-g[i].c] + g[i].p);
        }
    }
    int res = w;
    for(int i = 1; i <= w; ++i){
        if(f[i] >= m){
            res = i;
            break;
        }
    }
    cout << res << endl;
    return 0;
}