#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr int N = 400, INF = 1e9;

int f[N][N];
int s[N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) s[i] += s[i - 1];

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            f[i][j] = INF;
            for (int k = i; k < j; k++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
            }
        }
    }

    cout << f[1][n] << endl;
    return 0;
}