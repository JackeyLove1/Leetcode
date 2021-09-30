// Author: Jacky
// Date: 2021-09-29
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int debug = 0;
constexpr int N = 1e6 + 100;
bool isnp[N];
vector<int> primes; // 质数表
void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes) {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}

int main() {
    fhj();
    int n;
    cin >> n;
    init(n);
    cout << primes.size() << endl;
    return 0;
}