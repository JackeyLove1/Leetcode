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

static int f[11][10][3];
int a[20];

int dfs(int pos, int pre, bool limit) {
    if (pos == -1) return 1;
    int &v = f[pos][pre][limit];
    if (v != -1) return v;
    v = 0;
    int up = limit ? a[pos] : 9;
    for (int i = pre; i <= up; ++i) {
        v += dfs(pos - 1, i, limit && i == a[pos]);
    }
    return v;
}

int solve(int x) {
    if (!x) return 1;
    int pos = 0;
    memset(f, -1, sizeof f);
    while (x) {
        a[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos - 1, 0, true);
}


int main() {
    fhj();
    int l, r;
    while (cin >> l >> r) {
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}


