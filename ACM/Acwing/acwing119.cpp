// Author: Jacky
// Time: 2021-09-25
#include <iostream>
#include <vector>
#include <algorithm>
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

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int debug = 1;
constexpr int N = 2e5 + 100, INF = 0x3f3f3f3f;

struct node {
    double x, y;
    int f;
};

node a[N];

bool cmp(const node &x, const node &y) {
    if (x.x == y.x) return x.y < y.y;
    return x.x < y.x;
}

inline double calc(int x, int y) {
    if (a[x].f == a[y].f) return INF;
    double x1 = (a[x].x - a[y].x) * (a[x].x - a[y].x);
    double y1 = (a[x].y - a[y].y) * (a[x].y - a[y].y);
    return sqrt(x1 + y1);
}

int temp[N];

double divide(int l, int r) {
    double d = INF;
    if (l == r) return d;
    if (l + 1 == r) return calc(l, r);
    int mid = l + r >> 1;
    double d1 = divide(l, mid);
    double d2 = divide(mid + 1, r);
    d = d1 > d2 ? d2 : d1;
    int k = 0;
    //这边存到一个临时数组，直接n^2查找最近值，因为排序和没排差不多
    //(可以理性感受最多区域内只有6个点)
    for (int i = l; i <= r; ++i) {
        if (fabs(a[i].x - a[mid].x) < d) {
            temp[++k] = i;
        }
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = i + 1; j <= k; ++j) {
            double d3 = calc(temp[i], temp[j]);
            if (d3 < d) d = d3;
        }
    }
    return d;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].x >> a[i].y;
            a[i].f = 0;
        }
        for (int i = n + 1; i <= 2 * n; ++i) {
            cin >> a[i].x >> a[i].y;
            a[i].f = 1;
        }
        n *= 2;
        sort(a + 1, a + n + 1, cmp);
        printf("%.3lf\n", divide(1, n));
    }
    return 0;
}