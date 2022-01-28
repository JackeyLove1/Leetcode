#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int n;
constexpr int N = 1100;
int f[N];

int solve(int x) {
    if (x == 0) return 1;
    if(f[x]) return f[x];
    for (int i = 0; i <= x / 2; ++i) {
        f[x] += solve(i);
        // cout << "solve(i): " << i << " res: " << solve(i) << endl;
    }
    return f[x];
}

int main() {
    fhj();
    cin >> n;
    f[0] = 1;
    cout << solve(n) << endl;
    return 0;
}