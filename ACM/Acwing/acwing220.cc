#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>

using namespace std;
using ull = __int128;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e7 + 100;


int primes[N], cnt;
int euler[N];
bool st[N];
ll sum[N];

// 筛选法求欧拉函数
void get_eulers(int n) {
    euler[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}

int main() {
    fhj();
    int n;
    cin >> n;
    get_eulers(n);
    ll res = 0;
    for(int i = 1; i <= n; ++i) sum[i] = sum[i-1] + euler[i];
    for (int i = 0; i < cnt; ++i){
        int p = primes[i];
        res += sum[n / p] * 2 + 1;
    }
    cout << res << endl;
    return 0;
}