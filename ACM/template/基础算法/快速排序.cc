#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <climits>

using namespace std;

constexpr int N = 1e6 + 100;
int nums[N];
int n;

void qSort(int nums[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = nums[l + (r - l) / 2];
    while (i < j) {
        do ++i; while (nums[i] < x);
        do --j; while (nums[j] > x);
        if (i < j) swap(nums[i], nums[j]);
    }
    qSort(nums, l, j);
    qSort(nums, j + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    qSort(nums, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}