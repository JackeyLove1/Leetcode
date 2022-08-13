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

int main() {
    fhj();
    int n;
    string s;
    cin >> n;
    cin >> s;
    unordered_set<char> us;
    for (const auto &ch: s) {
        us.insert(std::tolower(ch));
    }
    if (us.size() == 26) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
