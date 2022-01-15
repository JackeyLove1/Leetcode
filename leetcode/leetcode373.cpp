#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
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

class Solution_wrong {
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
        int l = 0, r = 0;
        vector<vector<int>> res;
        res.reserve(k + 5);
        // res.push_back({nums1[0], nums2[0]});
        while (res.size() < k && (l < nums1.size() && r < nums2.size())) {
            if (l == nums1.size() - 1 && r == nums2.size()) {
                res.push_back({nums1[l], nums2[r]});
                break;
            }
            if (l == nums1.size() - 1) {
                res.push_back({nums1[l], nums2[r++]});
                continue;
            }
            if (r == nums2.size() - 1) {
                res.push_back({nums1[l++], nums2[r]});
                continue;
            }
            if (l < nums1.size() - 1 && r < nums2.size() - 1) {
                res.push_back({nums1[l], nums2[r]});
                if (nums1[l] + nums2[r + 1] < nums1[l + 1] + nums2[r]) {
                    ++r;
                } else {
                    ++l;
                }
            }

        }
        return res;
    }
};

class Solution {
private:
    struct node {
        int l, r;

        explicit node(int l_, int r_) : l(l_), r(r_) {}

        bool operator<(const node &rhs) const {
            return l + r > rhs.l + rhs.r;
        }
    };

    priority_queue<node> heap;
public:
    vector<vector<int>> kSmallestPairs(const vector<int> &nums1, const vector<int> &nums2, const int k) {
        for (const int num1 : nums1) {
            for (const int num2 : nums2) {
                // if (heap.size() >= k) break;
                heap.emplace(num1, num2);
            }
        }
        vector<vector<int>> res;
        res.reserve(k + 5);
        while (!heap.empty() && res.size() < k) {
            auto t = heap.top();
            res.push_back({t.l, t.r});
            heap.pop();
        }
        return res;
    }
};