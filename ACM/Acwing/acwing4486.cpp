#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;
int num, step;
vector<int> primes;
unordered_map<int, int> cnt;
using ll = long long;

int main() {
    int x;
    cin >> x;
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) {
                s++;
                x /= i;
            }
            primes.push_back(i);
            cnt[i] = s;
        }
    }
    if (x > 1) {
        primes.push_back(x);
        cnt[x] = 1;
    }
    int maxn = 0;
    for (const auto&[_, v] : cnt) maxn = max(maxn, v);
    bool flag = true;
    for (const auto&[_, v] : cnt) {
        if (v != maxn) {
            flag = false;
            break;
        }
    }
    int l = 0;
    while (maxn > std::pow(2, l)) ++l;
    if (std::pow(2, l) != maxn && flag) ++l;
    ll r = 1;
    for (const auto &num : primes) r *= static_cast<ll>(num);
    if (!flag) ++l;
    cout << r << " " << l << endl;
    return 0;
}