#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <unordered_map>

using namespace std;

class NumArray {
    static constexpr int N = 3e4 + 100;

    int tree[N];
    int n;
    vector<int> num;

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void init() {
        for (int i = 1; i <= n; ++i) {
            tree[i] += num[i - 1];
            int j = i + lowbit(i);
            if (j <= n) tree[j] += tree[i];
        }
    }

    inline void add(int i, int k) {
        while (i <= n) {
            tree[i] += k;
            i += lowbit(i);
        }
    }

    inline int sum(int x) { // 求a[1] ... a[x] 的和
        int sum = 0;
        while (x > 0) {
            sum += tree[x];
            x -= lowbit(x);
        }
        return sum;
    }

public:
    NumArray(vector<int> &nums) {
        num = nums;
        n = nums.size();
        memset(tree, 0, sizeof tree);
        init();
    }

    void update(int index, int val) {
        add(index + 1, val - num[index]);
        num[index] = val;
    }

    int sumRange(int left, int right) {
        return sum(right + 1) - sum(left);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */