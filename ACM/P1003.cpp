#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>

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

constexpr int N = 1e4 + 100;

int f[N][N];

struct Node {
    int a, b, g, k;

    Node(int _a, int _b, int _g, int _k)
            : a(_a), b(_b), g(_g), k(_k) {}
};

int n;

int main() {
    fhj();
    cin >> n;
    vector<Node> w;
    int a, b, g, k;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b >> g >> k;
        w.emplace_back(a, b, g, k);
    }
    int x, y;
    cin >> x >> y;
    reverse(w.begin(), w.end());
    int res = -1;
    for (int i = 0; i < w.size(); ++i) {
        int sx = w[i].a + w[i].g;
        int sy = w[i].b + w[i].k;
        if (x >= w[i].a && x <= sx && y >= w[i].b && y <= sy) {
            res = n - i;
            break;
        }
    }
    cout << res << endl;
    return 0;
}