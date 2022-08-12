#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e4 + 100, M = 1e5 + 100;

int n, primes[N], cnt;
bool vis[N];

inline void get_prime(int sz) {
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
    get_prime(1e4);
    while (scanf("%d", &n) != EOF) {
        int num = 0;
        for (int i = 0; i <= cnt; ++i) {
            if (primes[i] >= n) break;
            if (primes[i] % 10 == 1) {
                ++num;
                cout << primes[i] << " ";
            }

        }
        if (num == 0) {
            cout << -1;
        }
        cout << endl;
    }
    return 0;
}