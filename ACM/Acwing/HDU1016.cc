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


int n;
bool used[N];
int nums[N];

void dfs(int step) {
    if (step == n + 1) {
        if (isPrime(nums[n] + 1)) {
            for (int i = 1; i <= n; ++i) {
                cout << nums[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    for (int i = 2; i <= n; ++i) {
        if (!used[i]) {
            if (isPrime(i + nums[step - 1])) {
                used[i] = true;
                nums[step] = i;
                dfs(step + 1);
                used[i] = false;
                nums[step] = 0;
            }
        }
    }
}

int main() {
    init(N - 1);
    int cas = 0;
    while (cin >> n) {
        memset(nums, 0, sizeof nums);
        memset(used, false, sizeof used);
        printf("Case %d:\n",++cas);
        used[1] = true;
        nums[1] = 1;
        dfs(2);
    }
    return 0;
}
