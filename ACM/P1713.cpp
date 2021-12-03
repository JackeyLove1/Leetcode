#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1e3 + 100;
int f[N], s[N];
int n;

inline int solve(int x) {
    int sum = 0;
    for (int i = 1; i <= int(sqrt(x)); ++i) {
        if (x % i == 0) {
            sum += i + x / i;
        }
    }
    sum -= x;
    return sum;
}

int find(int x) {
    int ans = 0;
    for (int i = 1; i < x; i++)
        if (x % i == 0)
            ans += i;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        // s[i] = solve(i);
        s[i] = find(i);
        // cout << "i: " << i << " res: " << s[i] << endl;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >= i; --j) {
            f[j] = max(f[j - i] + s[i], f[j]);
        }
    }
    cout << f[n] << endl;
    return 0;
}