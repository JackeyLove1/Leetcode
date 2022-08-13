#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f;

int solve(const string &s) {
    int cnt = 0, r = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            ++cnt;
        } else {
            ++r;
            if (--cnt < 0) {
                cnt += 2;
                for (int j = i + 1; j < s.size(); ++j) {
                    if (s[i] == '(') {
                        ++cnt;
                    } else {
                        if (--cnt < 0) {
                            return 0;
                        }
                    }
                }
                return r;
            }
        }
    }
    return 0;
}

int main() {
    fhj();
    int n;
    string s;
    cin >> n >> s;
    int l = 0, r = 0;
    for (const auto c: s) {
        l += (c == '(');
        r += (c == ')');
    }
    if (r == l + 1) {
        cout << solve(s) << endl;
        return 0;
    } else if (l == r + 2) {
        reverse(s.begin(), s.end());
        for (auto &c: s) {
            if (c == '(') c = ')';
            else c = '(';
        }
        cout << solve(s) << endl;
        return 0;
    }
    cout << 0 << endl;
    return 0;
}