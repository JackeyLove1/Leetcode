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
int n, m, diff[N], a[N];
ll t[N];

inline int lowbit(int x) {
    return x & (-x);
}

inline void init() {
    for (int i = 1; i <= n; ++i) {
        t[i] += diff[i];
        int j = i + lowbit(i);
        if (j <= n) t[j] += t[i];
    }
}

inline ll getsum(int x) {
    ll sum = 0;
    for (int pos = x; pos; pos -= lowbit(pos)) {
        sum += t[pos];
    }
    return sum;
}

inline void update(int x, int v) {
    for (int pos = x; pos <= n; pos += lowbit(pos)) {
        t[pos] += v;
    }
}

inline void update(int l, int r, int v) {
    update(l, v);
    update(r + 1, -v);
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        diff[i] = a[i] - a[i - 1];
    }
    init();
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            if (l > r) swap(l, r);
            update(l, r, x);
        } else {
            int pos;
            cin >> pos;
            cout << getsum(pos) << endl;
        }
    }
    return 0;
}