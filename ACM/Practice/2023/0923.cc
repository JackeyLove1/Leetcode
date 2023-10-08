#include <bits/stdc++.h>
#include <array>
#include <algorithm>
#include <functional>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 1e6;
int nums[N];
int n;

void qSort(int nums[], int l, int r) {
    if (l >= r)return;
    int i = l - 1, j = r + 1;
    int x = nums[(l + r) >> 1];
    while (i < j) {
        do ++i; while (nums[i] < x);
        do --j; while (nums[j] > x);
        if (i < j) swap(nums[i], nums[j]);
    }
    qSort(nums, l, j);
    qSort(nums, j + 1, r);
}

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    qSort(nums, 0, n - 1);
    for (int i = 0;i < n; ++i) cout << nums[i] << " ";
    std::cout << std::endl;
    return 0;
}

#include <bits/stdc++.h>
#include <array>
#include <algorithm>
#include <functional>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 1e6;
int nums[N], tmp[N];
int n;

void mergeSort(int nums[], int l, int r) {
    if (l >= r)return;
    int mid = (l + r) >> 1;
    mergeSort(nums, l, mid), mergeSort(nums, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (nums[i] < nums[j]) tmp[k++] = nums[i++];
        else tmp[k++] = nums[j++];
    }
    while (i <= mid) tmp[k++] = nums[i++];
    while (j <= r) tmp[k++] = nums[j++];
    for (int i = l, k = 0; i <= r; i++, k++) nums[i] = tmp[k];
}

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    mergeSort(nums, 0, n - 1);
    for (int i = 0; i < n; ++i) cout << nums[i] << " ";
    std::cout << std::endl;
    return 0;
}

