// 二分查找模版题

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 1e6 + 1;
int n, m, k;

int q[N];

int lower_bound(int q[], int target) {
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (q[mid] >= target) r = mid;
        else l = mid + 1;
    }
    // cout << "l1: "<< l << endl;
    if (q[l] != target) return -1;
    return l;
}

int upper_bound(int q[], int target) {
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (q[mid] <= target) l = mid;
        else r = mid - 1;
    }
    // cout << "l2: "<< l << endl;
    if (q[l] != target) return -1;
    return l;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> q[i];
    while (m--) {
        cin >> k;
        cout << lower_bound(q, k) << " " << upper_bound(q, k) << endl;
    }
    return 0;
}