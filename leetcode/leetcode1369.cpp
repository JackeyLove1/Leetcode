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

class Solution {
public:
    int addRungs(vector<int> &rungs, int dist) {
        int cur = 0, step = 0;
        for (const int num : rungs) {
            if (cur + dist >= num) {
                cur = num;
                continue;
            }
            step += (num - cur - 1) / dist;
            cur = num;
        }
        return step;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {3, 6, 8, 10};
    cout << s.addRungs(v1, 3) << " res: 0" << endl;
    vector<int> v2 = {3, 4, 6, 7};
    cout << s.addRungs(v2, 2) << " res: 1" << endl;
    vector<int> v3 = {1};
    cout << s.addRungs(v3, 1) << " res: 2" << endl;
    return 0;
}