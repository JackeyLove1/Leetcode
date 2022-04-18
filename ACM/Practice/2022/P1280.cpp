#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1e4 + 100;
int f[N];
using PII = pair<int, int>;
unordered_map<int, vector<int>> um;
int n, k;

int main() {
    fhj();
    cin >> n >> k;
    int p, t;
    for (int i = 0; i < k; ++i) {
        cin >> p >> t;
        um[p].push_back(t);
    }
    for (int i = n; i >= 0; --i) {
        if (um.count(i)) {
            for (const auto &cost_time:um[i]) {
                f[i] = max(f[i], f[i+cost_time]);
            }
        } else {
            f[i] = f[i + 1] + 1;
        }
    }
    cout << f[1] << endl;
    return 0;
}

