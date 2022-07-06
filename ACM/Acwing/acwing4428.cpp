#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_set>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
using PII = pair<int, int>;

static constexpr int N = 1010 + 100, M = 20010 + 100;

int main() {
    fhj();
    int n;
    cin >> n;
    string s;
    cin >> s;
    unordered_set<char> us;
    for (int i = 0; i < n; ++i) {
        us.emplace(tolower(s[i]));
    }
    if (us.size() == 26) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}