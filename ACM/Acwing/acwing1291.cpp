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

int n;
const int N = 1e5 + 10, M = 1e6 + 10;
int cnt[M], nums[N], res[M];
bool st[M];

int main() {
    fhj();
    cin >> n;
    int maxn = 2;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        cnt[nums[i]]++;
        maxn = max(maxn, nums[i]);
    }
    for (int i = 1; i <= maxn; ++i) {
        if (!cnt[i]) continue;
        for (int j = 1; j * i <= maxn; ++j) {
            res[j * i] += cnt[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << res[nums[i]] - 1 << endl;
    }
    return 0;
}