#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

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

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2010;
int n, m;

struct good {
    int v, w;
    int k;

    good(int _v, int _w, int _k) : v(_v), w(_w), k(_k) {}
};

int f[N];

int main() {
    fhj();
    cin >> n >> m;
    vector<good> goods;
    int k, v, w;
    for (int t = 1; t <= n; ++t) {
        cin >> k >> v >> w;
        if (k == 1) {
            for (int i = 1; i <= m; ++i) {
                if (i * i * v - i * w <= 0) continue;
                goods.emplace_back(i, i * i * v - i * w, 0);
            }
        } else if (k == 2) {
            int c;
            cin >> c;
            for (int h = 1; h <= c; h <<= 1) {
                goods.emplace_back(h * v, h * w, 0);
                c -= h;
            }
            if (c) {
                goods.emplace_back(c * v, c * w, 0);
            }
        } else {
            goods.emplace_back(v, w, 1);
        }
    }
    for (auto &g : goods) {
        if (g.k) {
            for (int j = g.w; j <= m; ++j) {
                f[j] = max(f[j], f[j - g.w] + g.v);
            }
        } else {
            for (int j = m; j >= g.w; --j) {
                f[j] = max(f[j], f[j - g.w] + g.v);
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}