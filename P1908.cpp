#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e6 + 100;
int nums[N];
int temp[N];

LL merge_sort(int nums[], int l, int r) {
    if (l >= r) return 0;
    int mid = l + r >> 1;
    LL res = merge_sort(nums, l, mid) + merge_sort(nums, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (nums[i] > nums[j]) {
            res += mid - i + 1;
            temp[k++] = nums[j++];
        } else {
            temp[k++] = nums[i++];
        }
    }
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= r) temp[k++] = nums[j++];
    for (i = l, j = 0; i <= r; i++, j++) {
        nums[i] = temp[j];
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    LL res = merge_sort(nums, 0, n - 1);
    cout << res << endl;
    return 0;
}