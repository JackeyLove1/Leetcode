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

constexpr int N = 1e6, M = 1e5, INF = 0x3f3f3f3f;
int f[N];
int v[N], w[N];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = m; j >= w[i]; --j){
            f[j] = max(f[j], f[j-w[i]] + v[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}