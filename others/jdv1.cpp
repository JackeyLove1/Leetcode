#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

constexpr int N = 1e3 + 100;
int n, q, c;
vector<int> start[N];
vector<int> stop[N];
bool work[N];
const int debug = 1;

inline void add(int a, int b) {
    // 启动依赖
    start[a].push_back(b);
    // 关闭依赖
    stop[b].push_back(a);
}

inline int count() {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (work[i]) ++sum;
    }
    return sum;
}

inline void start_work(int idx) {
    queue<int> qs;
    qs.push(idx);
    // work[idx] = true;
    while (!qs.empty()) {
        auto t = qs.front();
        qs.pop();
        if (work[t]) continue;
        work[t] = true;
        for (auto &next : start[t]) {
            qs.push(next);
        }
    }
}

inline void stop_work(int idx) {
    queue<int> qs;
    qs.push(idx);
    // work[idx] = true;
    while (!qs.empty()) {
        auto t = qs.front();
        qs.pop();
        if (!work[t]) continue;
        work[t] = false;
        for (auto &next : stop[t]) {
            qs.push(next);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    int b;
    for (int a = 1; a <= n; ++a) {
        cin >> c;
        for (int i = 0; i < c; ++i) {
            cin >> b;
            add(a, b);
        }
    }
    int x, y;

    for (int i = 0; i < q; ++i) {
        cin >> x >> y;
        if (x == 1) {
            start_work(y);
            cout << count() << endl;
        } else {
            stop_work(y);
            cout << count() << endl;
        }
    }
    return 0;
}