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


constexpr int N = 110, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;

ull h[N][N], p[N];
vector<string> str;
int n, m;
constexpr ull P = 131;

inline ull get(int idx, int l, int r) {
    return h[idx][r + 1] - h[idx][l] * p[r - l + 1];
}

inline void init() {
    p[0] = 1;
    for (int i = 1; i < N; ++i) {
        p[i] = p[i - 1] * P;
    }
}

inline void str_hash() {
    for (int idx = 0; idx < m; ++idx) {
        const auto &s = str[idx];
        for (int i = 1; i <= s.size(); i++) {
            h[idx][i] = h[idx][i - 1] * P + s[i - 1];
        }
    }
}

int main() {
    // init();
    fhj();
    int t;
    cin >> t;
    while (t--) {
        str.clear();
        string s;
        cin >> m;
        int minl = 1e6, minx = -1;
        for (int i = 0; i < m; ++i) {
            cin >> s;
            if (s.size() < minl) {
                minx = i, minl = s.size();
            }
            str.emplace_back(s);
        }
        auto found = true;
        auto res = 0;
        for (int len = minl; len > 0; --len) {
            for (int i = 0; i + len <= str[minx].size(); ++i) {
                found = true;
                auto s1 = str[minx].substr(i, len);
                string s2{s1.begin(), s1.end()};
                reverse(s1.begin(), s1.end());
                // cout <<"s1: " << s1 <<" s2: " << s2 << endl;
                for (int j = 0; j < m; ++j) {
                    if (str[j].find(s1) == string::npos && str[j].find(s2) == string::npos) {
                        // cout <<"j: " << j <<" break" << endl;
                        found = false;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) {
                res = len;
                break;
            }
        }
        if (found){
            cout << res << endl;
        }else{
            cout << 0 << endl;
        }
    }
    return 0;
}