#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 310;
using ll = long long;

struct node {
    int a, b, w;

    explicit node(int a_, int b_, int w_) : a(a_), b(b_), w(w_) {}

    bool operator<(const node &rhs) const {
        return w < rhs.w;
    }
};


int p[N];
int n, m;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    fhj();
    cin >> n;
    vector<node> e;
    e.reserve(n * n + 10);
    for (int i = 0; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int w;
        cin >> w;
        e.emplace_back(0, i, w);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            cin >> w;
            if (i != j) {
                e.emplace_back(i, j, w);
            }
        }
    }
    sort(e.begin(), e.end());
    int res = 0;
    for (const auto &edge : e) {
        int a = find(edge.a), b = find(edge.b), w = edge.w;
        if (a != b) {
            p[a] = b;
            res += w;
        }
    }

    cout << res << endl;
    return 0;
}