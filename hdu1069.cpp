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

constexpr int N = 200, INF = 0x7fffffff;

struct node {
    int x, y, h;
} a[N];
int f[N];

int main() {
    fhj();
    int n, kcase = 1;
    while (cin >> n && n) {
        memset(f, 0, sizeof f);
        int k = 1;
        for (int i = 1; i <= n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            a[k++] = {max(x, y), min(x, y), z};
            a[k++] = {max(x, z), min(x, z), y};
            a[k++] = {max(y, z), min(y, z), x};
        }
        sort(a + 1, a + k, [](node &n1, node &n2) {
            if (n1.x == n2.y) {
                return n1.y > n2.y;
            }
            return n1.x > n2.x;
        });
        int maxn = 1;
        for (int i = 1; i < k; ++i) {
            f[i] = a[i].h;
            for (int j = 1; j < i; ++j) {
                if (a[j].x > a[i].x && a[j].y > a[i].y) {
                    f[i] = max(f[i], f[j] + a[i].h);
                    maxn = max(maxn, f[i]);
                }
            }
        }
        printf("Case %d: maximum height = %d\n", kcase++, maxn);
    }
    return 0;
}