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

int main() {
    init(N - 1);
    int m, a, b;
    while (~scanf("%d%d%d", &m, &a, &b) && (m || a || b)) {
        int ansa, ansb, maxans = 0;
        const int m2 = m / 2;
        const double ratio = (double) a / b;
        for (int i = 0; i < cnt && primes[i] <= m2; ++i) {
            for (int j = i; j < cnt && primes[j] <= m2; ++j) {
                int now = primes[i] * primes[j];
                if (now <= m && now > maxans && ((double) primes[i] / primes[j] >= ratio)) {
                    ansa = primes[i], ansb = primes[j];
                }
            }
        }
        cout << ansa << " " << ansb << endl;
    }
    return 0;
}
