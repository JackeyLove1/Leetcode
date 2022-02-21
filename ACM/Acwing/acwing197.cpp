#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

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

const int N = 1e6 + 10;
int n, primes[N], cnt;
bool vis[N];

inline void get_prime(int sz) {
    memset(vis, 0, sizeof vis);
    for (int i = 2; i <= sz; i++) {
        if (!vis[i]) primes[cnt++] = i;
        for (int j = 0; j <= cnt && i * primes[j] <= sz; ++j) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    fhj();
    cin >> n;
    get_prime(n);
    for (int i = 0; i < cnt; ++i) {
        int p = primes[i], s = 0;
        for (int j = n; j; j /= p) s += j / p;
        printf("%d %d\n", p, s);
    }
    return 0;
}