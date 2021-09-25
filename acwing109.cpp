// Author: Jacky
// Time: 2021-09-24
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1e6 + 10;
using ll = long long;
ll w[N];
ll t[N];
int n, m;
ll T;

inline ll sqrt(ll x) {
    return x * x;
}

inline ll get(int l, int r) {
    int k = 0;
    for (int i = l; i < r; ++i) {
        t[k++] = w[i];
    }
    ll sum = 0;
    sort(t, t + k);
    for (int i = 0; i < m && i < k; i++, k--) {
        sum += sqrt(t[i] - t[k - 1]);
    }
    return sum;
}

int main() {
    fhj();
    int K;
    cin >> K;
    while (K--) {
        cin >> n >> m >> T;
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
        }
        int res = 0;
        int start = 0, end = 0;
        while (end < n) {
            int len = 1;
            while (len) {
                if (end + len <= n && get(start, end + len) <= T) {
                    end += len, len <<= 1;
                } else {
                    len >>= 1;
                }
            }
            start = end;
            ++res;
        }
        cout << res << endl;
    }
    return 0;
}