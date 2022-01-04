#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

int n, mid, cnt;
constexpr int N = 30;
const int S = (1 << 20) + 20;
int nums[N];
unordered_map<int, int> mp;
vector<int> g[S];
bool vis[N];

void dfs1(int x, int sum, int state) {
    if (x > mid) {
        if (!mp.count(sum)) mp[sum] = ++cnt; // 离散化
        g[mp[sum]].push_back(state);
        return;
    }
    dfs1(x + 1, sum, state);
    dfs1(x + 1, sum - nums[x], state | (1 << (x - 1)));
    dfs1(x + 1, sum + nums[x], state | (1 << (x - 1)));
}

void dfs2(int x, int sum, int state) {
    if (x > n) {
        if (mp.count(sum)) {
            int t = mp[sum];
            for (auto s : g[t]) {
                vis[s | state] = 1;
            }
        }
        return;
    }
    dfs2(x + 1, sum, state);
    dfs2(x + 1, sum + nums[x], state | ((1 << (x - 1))));
    dfs2(x + 1, sum - nums[x], state | ((1 << (x - 1))));
}

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    mid = n >> 1;
    dfs1(1, 0, 0), dfs2(mid + 1, 0, 0);
    int ans = 0;
    for (int i = 0; i <= (1 << n); ++i) {
        ans += vis[i];
    }
    cout << ans << endl;
    return 0;
}