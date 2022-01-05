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

class Solution {
public:
    vector<int> replaceElements(vector<int> &arr) {
        vector<int> f;
        f.reserve(arr.size() + 10);
        f.push_back(-1);
        int max_num = arr.back();
        for (int i = arr.size() - 2; i >= 0; --i) {
            max_num = max(max_num, arr[i + 1]);
            f.push_back(max_num);
        }
        reverse(f.begin(), f.end());
        return f;
    }
};