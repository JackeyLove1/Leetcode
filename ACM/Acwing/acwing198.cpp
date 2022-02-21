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

typedef long long LL;

int n;
int s;
int maxd;
int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

void dfs(int u, int last, int p, int sum) {
    if (sum > maxd || sum == maxd && p < s) {
        maxd = sum;
        s = p;
    }
    if (u == 9) return;
    for (int i = 1; i <= last; ++ i) {
        if ((LL)p * primes[u] > n) return;
        p *= primes[u];
        dfs(u + 1, i, p, sum * (i + 1));
    }
}

int main() {
    cin >> n;
    dfs(0, 30, 1, 1);
    cout << s << endl;
    return 0;
}