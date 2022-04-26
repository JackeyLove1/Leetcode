#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <cmath>
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

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 100010, M = 350;

int n, m, len;
ll add[M], sum[M];
int w[N];

inline int get(int x) {
    return static_cast<int>(x / len);
}

void change(int l, int r, int d) {
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++i) {
            w[i] += d;
            sum[get(i)] += d;
        }

    } else {
        int i = l, j = r;
        while (get(i) == get(l)) w[i] += d, sum[get(l)] += d, i++;
        while (get(j) == get(r)) w[j] += d, sum[get(r)] += d, j--;
        for (int k = get(i); k <= get(j); ++k) {
            sum[k] += 1l * len * d;
            add[k] += d;
        }
    }
}

ll query(int l, int r) {
    ll res = 0;
    if (get(l) == get(r)) {
        for (int i = l; i <= r; ++i) {
            res += w[i] + add[get(i)];
        }
        return res;
    }
    int i = l, j = r;
    while (get(i) == get(l)) res += w[i] + add[get(i)], i++;
    while (get(j) == get(r)) res += w[j] + add[get(j)], j--;
    for (int k = get(i); k <= get(j); ++k) {
        res += sum[k];
    }
    return res;
}
/*
int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        sum[get(i)] += w[i];
    }
    len = static_cast<int>(sqrt(n));
    int l, r, d;
    char op;
    while (m--) {
        cin >> op;
        if (op == 'Q') {
            cin >> l >> r;
            cout << query(l, r) << endl;
        } else {
            cin >> l >> r >> d;
            change(l, r, d);
        }
    }
    return 0;
}
*/
int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }

    char op[2];
    int l, r, d;
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C')
        {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }

    return 0;
}

