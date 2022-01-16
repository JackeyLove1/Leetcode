#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;
constexpr int N = 1e3 + 100;
bool isnp[N];
vector<int> primes; // 质数表
void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes) {
            if (p * i > n)
                break;
            isnp[p * i] = true;
            if (i % p == 0)
                break;
        }
    }
}

int n;
using ll = long long;
ll f[N];

int main() {
    cin >> n;
    init(n + 1);
    f[0] = 1;
    for (auto &num : primes) {
        for (int i = num; i <= n; ++i) {
            f[i] += f[i - num];
        }
    }
    cout << f[n] << endl;
    return 0;
}