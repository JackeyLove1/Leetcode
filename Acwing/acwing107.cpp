// Author: Jacky
// Time: 2021-09-22
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

constexpr int N = 1e6 + 100;
int a[N], tmp[N];
using ll = long long;
const int debug = 0;

ll mergeSort(int nums[], int l, int r) {
    if (l >= r) return 0;
    int mid = l + r >> 1;
    ll res = mergeSort(nums, l, mid) + mergeSort(nums, mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (nums[i] > nums[j]) {
            res += mid - i + 1;
            tmp[k++] = a[j++];
        } else {
            tmp[k++] = a[i++];
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (i = l, j = 0; i <= r; i++, j++) {
        a[i] = tmp[j];
    }
    if (debug) cout << "l: " << l << " r: " << r << " res: " << res << endl;
    return res;
}

int n;

int main() {
    fhj();
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        ll cnt = mergeSort(a, 1, n);
        cout << cnt << endl;
    }
    return 0;
}