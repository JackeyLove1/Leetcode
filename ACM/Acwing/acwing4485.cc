#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
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
constexpr int N = 1e5 + 1000;
int e[N], h[N], ne[N], w[N], idx = 0;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int main() {
    fhj();
    int n;
    cin >> n;
    vector<int> a, b;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        cin >> x;
        b.push_back(x);
    }
    if (accumulate(a.begin(), a.end(), 0) >= accumulate(b.begin(), b.end(), 0)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}