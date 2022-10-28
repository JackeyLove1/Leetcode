#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

constexpr int N = 1e5 + 100;

int nums[N];
char g[4];
unordered_set<string> uset;
const int per[4][4] = {{0, 1, 2, 3},
                       {2, 0, 3, 1},
                       {3, 2, 1, 0},
                       {1, 3, 0, 2}};
int cnt = 0;

void make_graph() {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> g[i * 2 + j];
        }
    }
    vector<string> v;
    v.reserve(4);
    string tmp{};
    for (int i = 0; i < 4; ++i) {
        tmp.clear();
        for (int j = 0; j < 4; ++j) {
            tmp.push_back(g[per[i][j]]);
        }
        if (uset.count(tmp)) return;
        v.emplace_back(tmp);
    }
    for (auto &strs: v) uset.emplace(strs);
    ++cnt;
}

int main() {
    fhj();
    string s;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        make_graph();
        if (i != n) cin >> s;
    }
    cout << cnt << endl;
    return 0;
}