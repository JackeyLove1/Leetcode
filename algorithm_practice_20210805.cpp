#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;

template<typename T>
inline void print1(const vector<T> &nums) {
    // for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    for (const auto &num : nums) { cout << num << " "; }
    cout << endl;
}

template<typename T>
inline void print2(const vector<vector<T>> &nums) {
    for_each(nums.begin(), nums.end(), [](const vector<T> &num) { print1(num); });
}

// 1.permutation
void permutation1(int n) {
    vector<int> nums;
    for (int i = 1; i <= n; i++) nums.push_back(i);
    do print1(nums); while (next_permutation(nums.begin(), nums.end()));
}

// string hash
using ULL = unsigned long long;
constexpr int P = 131;

inline ULL get(vector<ULL> &h, vector<ULL> &p, int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

inline void calculate(string &str, vector<ULL> &h, vector<ULL> &p) {
    int n = str.size();
    h.resize(n + 2, 0), p.resize(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + str[i - 1];
        p[i] = p[i - 1] * P;
    }
}

// quick sort
void quick_sort(vector<int> &nums, int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, mid = nums[l + r >> 1];
    while (i < j) {
        do i++; while (nums[i] < mid);
        do j--; while (nums[j] > mid);
        if (i < j) swap(nums[i], nums[j]);
    }
    quick_sort(nums, l, j), quick_sort(nums, j + 1, r);
}

// merge_sort
int tmp[N];

void merge_sort(vector<int> &nums, int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(nums, l, mid), merge_sort(nums, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (nums[i] < nums[j]) tmp[k++] = nums[i++];
        else tmp[k++] = nums[j++];
    }
    while (i <= mid) tmp[k++] = nums[i++];
    while (j <= r) tmp[k++] = nums[j++];
    for (i = l, j = 0; i <= r; i++, j++) {
        nums[i] = tmp[j];
    }
}

// heap sort
int heap[N];
int heapSize;

void down(int u) {
    int t = u;
    if (2 * u <= heapSize && heap[2 * u] < heap[t]) t = 2 * u;
    if (2 * u + 1 <= heapSize && heap[2 * u + 1] < heap[t]) t = 2 * u + 1;
    if (t != u) {
        swap(heap[t], heap[u]);
        down(t);
    }
}

void build(vector<int> &nums) {
    heapSize = nums.size();
    for (int i = 0; i < heapSize; i++) heap[i + 1] = nums[i];
    for (int i = heapSize / 2; i > 0; i--) down(i);
}

void heap_sort(vector<int> &nums) {
    build(nums);
    int cnt = nums.size();
    for (int i = 0; i < nums.size(); i++) {
        cout << heap[1] << " ";
        heap[1] = heap[heapSize--];
        down(1);
    }
}

// binary search target <= x
int my_lower_bound(vector<int> &nums, int target) {
    // if (nums.front() > target || nums.back() < target) return -1;
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (nums[mid] >= target) r = mid;
        else l = mid + 1;
    }
    if (nums[l] != target) return -1;
    return l;
}

// target < x
int my_upper_bound(vector<int> &nums, int target) {
    // if (nums.front() > target || nums.back() < target) return -1;
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (nums[mid] <= target) l = mid;
        else r = mid - 1;
    }
    if (nums[l] != target) return -1;
    return l;
}

int main() {
    // vector<int> nums1 = {1,2,3,4,5};
    // print1(nums1);
    // vector<vector<int>> nums2 = {{1,2}, {3,4}, {5,6}};
    // print2(nums2);
    // permutation1(3);
    // permutation1(5);
    // vector<int> nums = {1, 2, 1, 2, 3, 4, 1, -1, 100, 999, -9, 676767, 5, 6, 7, 8, 0, 0, 0, 10000};
    // quick_sort(nums, 0, nums.size() - 1);
    // heap_sort(nums);
    // cout << endl;
    // merge_sort(nums, 0, nums.size() - 1);
    // print1(nums);
    // vector<int> nums = {-2, -1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // cout << (lower_bound(nums.begin(), nums.end(), 0) - nums.begin()) << " "
         // << (upper_bound(nums.begin(), nums.end(), 0) - nums.begin()) << endl;
    // cout << my_lower_bound(nums, 0) << " " << my_upper_bound(nums, 0) << endl;
}