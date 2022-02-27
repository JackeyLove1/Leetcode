#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

int n, m;
constexpr int N = 32100, M = 70;
using PII = pair<int, int>; // v, w
int f[N];
PII master[M];
vector<PII> slave[M];
#define x first
#define y second

int main() {
    fhj();
    cin >> m >> n;
    int v, w, q;
    for (int i = 1; i <= n; ++i) {
        cin >> v >> w >> q;
        w *= v;
        if (!q) master[i] = {v, w};
        else slave[q].emplace_back(v, w);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 0; --j) {
            for (int k = 0; k < (1 << slave[i].size()); ++k) {
                v = master[i].x, w = master[i].y;
                for (int l = 0; l < slave[i].size(); ++l) {
                    if ((1 << l) & k) v += slave[i][l].x, w += slave[i][l].y;
                }
                if (j >= v) f[j] = max(f[j], f[j - v] + w);
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}