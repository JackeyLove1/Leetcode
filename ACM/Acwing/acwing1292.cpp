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
int n, m, primes[N], cnt;
bool vis[N];

inline void get_prime() {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) primes[++cnt] = i;
        for (int j = 1; j <= cnt && i * primes[j] <= n; ++j) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    fhj();
    n = N;
    get_prime();
    while (cin >> m && m) {
        for (int i = 1;; ++i) {
            int a = primes[i];
            int b = m - a;
            if (!vis[b]) {
                printf("%d = %d + %d\n", m, a, b);
                break;
            }
        }
    }
    return 0;
}