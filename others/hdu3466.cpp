// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 550, M = 1e4, INF = 0x7fffffff;

struct node {
    int p, q, v;
} a[N];

int f[M];

int main() {
    fhj();
    int n, m;
    int p, q, v;
    while (cin >> n >> m && n && m) {
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            cin >> p >> q >> v;
            a[i] = {p, q, v};
        }
        sort(a + 1, a + n + 1, [](node &n1, node &n2) {
            return n1.q - n1.p < n2.q - n2.p;
        });
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= a[i].p; --j) {
                if (f[j] >= a[i].q) {
                    f[j] = max(f[j], f[j - a[i].p] + a[i].v);
                } else {
                    break;
                }
            }
        }
        cout << f[m] << endl;
    }
    return 0;
}