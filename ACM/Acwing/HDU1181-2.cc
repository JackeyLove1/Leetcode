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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1100, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
bool st[N];


int main() {
    vector<string> words;
    string str;
    while (cin >> str && str != "0") {
        words.emplace_back(str);
    }
    const int n = words.size();
    memset(st, false, sizeof st);
    vector<int> g[n + 1];
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (words[i].front() == 'b') {
            q.push(i);
        }
        for (int j = i + 1; j < n; ++j) {
            if (words[i].back() == words[j].front()) {
                g[i].push_back(j);
            }
            if (words[j].back() == words[i].front()) {
                g[j].push_back(i);
            }
        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = true;
        for (auto &next: g[t]) {
            if (!st[next]) {
                if (words[next].back() == 'm') {
                    cout << "Yes." << endl;
                    return 0;
                }
                q.push(next);
            }
        }
    }
    cout << "No." << endl;
    return 0;
}