#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 1005;
int n, m;
vector<int> v1, v2;
set<int> s1, s2;

void dfs(vector<int> &v, set<int> &s, int step, int cur) {
    if (step == v.size()) {
        s.emplace(cur);
        return;
    }
    dfs(v, s, step + 1, cur + v[step]);
    dfs(v, s, step + 1, cur - v[step]);
}


int main() {
    fhj();
    int x;
    cin >> n;
    m = n >> 1;
    for (int i = 1; i <= m; ++i) {
        cin >> x;
        v1.emplace_back(x);
    }
    for (int i = m + 1; i <= n; ++i) {
        cin >> x;
        v2.emplace_back(x);
    }
    dfs(v1, s1, 0, 0);
    dfs(v2, s2, 0, 0);
    for (const auto &num1: s1) {
        for (const auto &num2: s2) {
            if ((num1 + num2) % 360 == 0 || num1 + num2 == 0) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}