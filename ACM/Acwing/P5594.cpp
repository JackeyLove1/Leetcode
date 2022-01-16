#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 110;

int n, m, k, tot[1004], vis[1004][1004], a[1004][1004];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!vis[j][a[i][j]]) {
                vis[j][a[i][j]] = 1;
                tot[a[i][j]]++;
            }
        }
    }
    for (int i = 1; i <= k; ++i)
        printf("%d ", tot[i]);
    return 0;
}