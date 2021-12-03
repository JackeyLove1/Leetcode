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

int main() {
    fhj();
    int n, k;
    cin >> n >> k;
    queue<int> q;
    f[n] = 0;
    q.push(n);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        if (t + 1 <= M && !f[t + 1]) {
            f[t + 1] = f[t] + 1;
            q.push(t + 1);
            if (t + 1 == k) break;
        }
        if (t * 2 <= M && !f[t * 2]) {
            f[t * 2] = f[t] + 1;
            q.push(t * 2);
            if (t * 2 == k) break;
        }
        if (t - 1 >= 0 && !f[t - 1]) {
            f[t - 1] = f[t] + 1;
            q.push(t - 1);
            if (t - 1 == k) break;
        }
    }
    cout << f[k] << endl;
    return 0;
}