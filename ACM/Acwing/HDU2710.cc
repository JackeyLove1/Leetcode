
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<algorithm>

typedef long long LL;
using namespace std;
const int maxn = 20005;
int primes[maxn];

inline void get_primes(const int n) {
    memset(primes, 0, sizeof(primes));
    primes[1] = 1;
    for (int i = 2; i < n; i++)//筛选所有范围内的最大素数因子
    {
        if (!primes[i]) {
            for (int j = i; j < n; j += i) {
                primes[j] = i;
            }
        }
    }
}

int main() {
    int n, m, MAX, p;
    get_primes(maxn-1);
    while (cin >> n) {
        MAX = -1;
        while (n--) {
            cin >> m;
            if (primes[m] > MAX) {
                MAX = primes[m];
                p = m;
            }
        }
        cout << p << endl;
    }
    return 0;
}