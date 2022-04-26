#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <list>
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

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 300010, M = 3100010;
using ll = long long;
using PII = pair<int, int>;
int n, m;
int a[N], s[N];
vector<int> alls;
vector<PII> add, query;

inline int find(int x) {

    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;

    // return lower_bound(alls.begin(), alls.end(), x) - alls.begin() + 1;
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x, c;
        cin >> x >> c;
        add.emplace_back(x, c);
        alls.emplace_back(x);
    }

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        query.emplace_back(l, r);
        alls.emplace_back(l);
        alls.emplace_back(r);
    }

    // deduplicate
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    // add
    for (const auto &v : add) {
        int x = find(v.first);
        a[x] += v.second;
    }

    // prefix_sum
    for (int i = 1; i <= alls.size(); ++i) {
        s[i] = s[i - 1] + a[i];
    }

    // query
    for (const auto &q : query) {
        int l = find(q.first), r = find(q.second);
        cout << s[r] - s[l - 1] << endl;
    }
    return 0;
}