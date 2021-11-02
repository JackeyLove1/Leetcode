#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 1e6 + 100;
using ll = long long;
int n, m, a[N];
ll t[N];

inline int lowbit(int x) {
    return x & (-x);
}

void init() {
    for (int i = 1; i <= n; ++i) {
        t[i] += a[i];
        int j = i + lowbit(i);
        if (j <= n) t[j] += t[i];
    }
}

inline void add(int i, int x) {
    for (int pos = i; pos <= n; pos += lowbit(pos)) {
        t[pos] += x;
    }
}

inline ll query(int l) {
    ll sum = 0;
    for (int pos = l; pos; pos -= lowbit(pos)) {
        sum += t[pos];
    }
    return sum;
}

inline ll query(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    init();
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            add(l, r);
        } else {
            cout << query(l, r) << endl;
        }
    }
    return 0;
}