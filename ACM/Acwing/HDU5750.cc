#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

using ll = long long;
using PII = pair<int, int>;

const int N = 1e6 + 10, M = 1250;
int primes[N];;
bool st[N];
int cntf, cnt, cntd;

// 获得n范围内所有质数
inline void init(int n) {
    memset(st, false, sizeof st);
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[cnt++] = i;
            for (int j = 0; primes[j] <= n / i; ++j) {
                st[primes[j] * i] = true;
                if (i % primes[j] == 0) break;
            }
        }
    }
}

inline int isPrime(int x) {
    int i;
    for (i = 2; i * i <= x; i++)
        if (x % i == 0)return 0;
    return 1;
}

int n, d;

int main() {
    init(N - 1);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &d);
        int i;
        for (i = 0; i < cnt; ++i){
            if (d * primes[i] >= n) break;
            if (d < primes[i]) break;
            if (d % primes[i] == 0) break;
        }
        if (d * primes[i] >= n || d < primes[i]) --i;
        cout << i << endl;
    }
    return 0;
}
