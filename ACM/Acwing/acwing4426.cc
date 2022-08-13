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
constexpr int N = 3e5 + 100, INF = 0x3f3f3f3f;
int f[N];

int main() {
    fhj();
    string s;
    cin >> s;
    ll res = 0;
    memset(f, 0, sizeof f);
    const int n = s.size();
    for (int i = 0; i < n; ++i) {
        if ((s[i] - '0') % 4 == 0) {
            f[i] += 1;
        }
        if (i > 0 && stoi(s.substr(i - 1, 2)) % 4 == 0) {
            f[i] += i;
        }
        res += f[i];
    }
    cout << res << endl;
    return 0;
}