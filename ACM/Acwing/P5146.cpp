#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6 + 100;
int n;
ll w[N];

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    ll minv = w[1], res = INT64_MIN;
    for (int i = 2; i <= n; ++i) {
        res = max(res, w[i] - minv);
        minv = min(minv, w[i]);
    }
    cout << res << endl;
    return 0;
}