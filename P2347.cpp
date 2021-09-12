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
int n, m;
int q[100];
bitset<N> f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 0; i < 6; ++i) {
        cin >> q[i];
    }
    f[0] = true;
    const int num[] = {1, 2, 3, 5, 10, 20};
    for (int i = 0; i < 6; ++i) {
        for (int j = 1; j <= q[i]; ++j) {
            f |= f << num[i];
            // cout << f << endl;
        }
    }
    cout << f.count() - 1 << endl;
    return 0;
}