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

int main() {
    fhj();
    int a, b, n;
    cin >> a >> b >> n;
    int d = b - a;
    ll res = 0;
    res = (ll) a * n + (ll) d * (n - 1) * n / 2;
    cout << res << endl;
    return 0;
}