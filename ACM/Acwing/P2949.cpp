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

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1e3 + 100;
int n, m;

int main() {
    fhj();
    cin >> n;
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    vector<PII> goods;
    goods.reserve(n + 1);
    for (int i = 1; i <= n; ++i) {
        int t, v;
        cin >> t >> v;
        goods.emplace_back(t, v);
    }
    sort(goods.begin(), goods.end(), [](const PII &p1, const PII &p2) {
        return p1.first == p2.first ? p1.second > p2.second : p1.first < p2.first;
    });
    using ll = long long;
    ll res = 0;
    for (const auto &g : goods) {
        if (g.first <= heap.size()) {
            auto t = heap.top();
            if (t.second < g.second) {
                heap.pop();
                res += static_cast<ll>(g.second - t.second);
                heap.push(g);
            }
        } else {
            heap.push(g);
            res += static_cast<ll>(g.second);
        }
    }
    cout << res << endl;
    return 0;
}
// 42960986814217