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

constexpr int N = 22, M = 35, INF = 0x3f3f3f3f;

int n, m, d[N][N], f[(1 << N) - 1], res = 0;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

int main() {
    fhj();
    cin >> n >> m;
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a;
        while (a--) {
            cin >> b;
            --b;
            d[i][b] = 1;
        }
    }
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << m; ++j) {
            if (cnt(j) == i) {
                for (int k = 0; k < m; ++k) {
                    if(!(j & (1 << k)) && d[i][k]){
                        auto s = j | (1 << k);
                        f[s] += f[j];
                    }
                }
            }
        }
    }
    int res = 0;
    for(int i = 0; i < 1 << m; ++i){
        if(cnt(i) == n) res += f[i];
    }
    cout << res << endl;
    return 0;
}