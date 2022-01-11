#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class TreeNode {
public:
    int val;
    TreeNode *left, *right;

    explicit TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    struct node {
        int p, g;
        int all;

        explicit node(int p_, int g_) : p(p_), g(g_), all(p_ + g_) {}
    };

public:
    int earliestFullBloom(vector<int> &plantTime, vector<int> &growTime) {
        vector<node> vec;
        int sz = plantTime.size();
        vec.reserve(sz + 10);
        for (int i = 0; i < sz; ++i) {
            vec.emplace_back(plantTime[i], growTime[i]);
        }
        // 开花时间唱的先种,总长度长的优先
        sort(vec.begin(), vec.end(), [](const node &x, const node &y) {
            return x.g == y.g ? x.all > y.all : x.g > y.g;
        });
        int st = 0;
        int ed = 0;
        for (const auto &num : vec) {
            ed = max(ed, st + num.all);
            st = num.p + st;
        }
        return ed;
    }
};