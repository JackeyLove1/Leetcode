#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

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

int n;
constexpr int N = 1010;

struct data {
    int a, b;

    bool operator<(const data &rhs) const {
        return a < rhs.a && b < rhs.b;
    }
} d[N];

// int edge[N][N];
int f[N];

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> d[i].a >> d[i].b;
            if (d[i].a > d[i].b) {
                swap(d[i].a, d[i].b);
            }
        }
        sort(d, d + n - 1);
        memset(f, 0, sizeof f);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            f[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (d[j] < d[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
        cout << res << endl;
    }
    return 0;
}