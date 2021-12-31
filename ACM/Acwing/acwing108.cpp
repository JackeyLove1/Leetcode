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

const int N = 510;
int n, m, a[N * N], b[N * N], c[N * N], i, j, k;
long long cnt;

void merge(int a[], int l, int r) {
    if (r - l < 1)
        return;
    int mid = (l + r) >> 1;
    merge(a, l, mid);
    merge(a, mid + 1, r);
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (j > r || i <= mid && a[i] <= a[j])
            b[k] = a[i++];
        else {
            cnt += mid - i + 1;
            b[k] = a[j++];
        }
    }
    for (int k = l; k <= r; k++)
        a[k] = b[k];
}

signed main() {
    fhj();
    while (cin >> n) {
        int ok = 0, x;
        for (i = 1; i <= n * n; i++) {
            cin >> x;
            if (x == 0)
                ok = 1;
            else
                a[i - ok] = x;
        }
        ok = 0;
        for (i = 1; i <= n * n; i++) {
            cin >> x;
            if (x == 0)
                ok = 1;
            else
                c[i - ok] = x;
        }
        cnt = 0;
        memset(b, 0, sizeof(b));
        merge(a, 1, n * n);
        long long ans = cnt;
        memset(b, 0, sizeof(b));
        cnt = 0;
        merge(c, 1, n * n);
        if ((ans & 1) == (cnt & 1))
            puts("TAK");
        else
            puts("NIE");
    }
    return 0;
}
