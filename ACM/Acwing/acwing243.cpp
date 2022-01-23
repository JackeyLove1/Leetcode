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
#include <stack>


#pragma GCC optimize(2)

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


using PII = pair<int, int>;
constexpr int N = 100010, M = 350;
using ll = long long;

int n, m, len;
ll add[M], sum[M];
int w[N];

inline int get(int i) {
    return i / len;
}

void change(int l, int r, int d) {
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++r) w[i] += d, sum[get(l)] += d;
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, ++i;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, --j;
        for (int k = get(i); k <= get(j); ++k) sum[k] += d * len, add[k] += d;
    }
}

ll query(int l, int r) {
    ll res = 0;
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++i) res += w[i] + add[get(i)];
    } else {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], ++i;
        while (get(j) == get(r)) res += w[j] + add[get(j)], --j;
        for (int k = get(i); k <= get(j); ++k) res += sum[k];
    }
    return res;
}

int main() {
    fhj();
    cin >> n >> m;
    len = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        sum[get(i)] += w[i];
    }

    char op[2];
    int l, r, d;
    while (m--) {
        cin >> op >> l >> r;
        if (*op == 'C') {
            cin >> d;
            change(l, r, d);
        }
        cout << query(l, r) << endl;
    }
    return 0;
}