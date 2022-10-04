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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100;
int n, m;
bool st[N];
vector<vector<int>> res;

void dfs(int step, int cur) {
    if (step > n && cur != m) return;
    if (cur == m) {
        vector<int> tmp;
        tmp.reserve(m);
        for (int i = 1; i <= n; ++i) {
            if (st[i]) tmp.push_back(i);
        }
        res.emplace_back(tmp);
        return;
    }
    dfs(step + 1, cur);
    st[step] = true;
    dfs(step + 1, cur + 1);
    st[step] = false;
}

int main() {
    cin >> n >> m;
    memset(st, 0, sizeof st);
    dfs(1, 0);
    sort(res.begin(), res.end(), [&](const vector<int> &v1, const vector<int> &v2) {
        for (int i = 0; i < m; ++i) {
            if (v1[i] > v2[i]) {
                return false;
            }
        }
        return true;
    });
    for (const auto &vec: res) {
        for (const auto num: vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}