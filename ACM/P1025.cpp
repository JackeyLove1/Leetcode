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
#include <cmath>
#include <set>

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

using ll = long long;

constexpr int N = 110;
int w[N];

inline int cnt(int x) {
    return __builtin_popcount(x);
}

int n, k;
int res = 0;

void dfs(int last, int sum, int cur) {
    if (cur == k) {
        if (sum == n) ++res;
        return;
    }
    for (int i = last; sum + i * (k - cur) <= n; ++i) {
        dfs(i, sum + i, cur + 1);
    }

}

int main() {
    fhj();
    cin >> n >> k;
    dfs(1, 0, 0);
    cout << res << endl;
    return 0;
}