#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
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
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

const int N = 100010, M = N * 2;

int main() {
    fhj();
    map<string, string> mp = {
            {"po", "FILIPINO"},
            {"su", "JAPANESE"},
            {"da", "KOREAN"}
    };
    string s;
    int m;
    cin >> m;
    while (m--) {
        cin >> s;
        auto res = mp[s.substr(s.size() - 2, 2)];
        cout << res << endl;
    }
    return 0;
}