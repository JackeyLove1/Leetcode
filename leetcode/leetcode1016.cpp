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
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool queryString(string s, int n) {
        s = static_cast<const string>(s);
        std::function<string(int)> trans = [](int x) -> string {
            string res;
            while (x) {
                res.push_back(((x & 1) + '0'));
                x >>= 1;
            }
            reverse(res.begin(), res.end());
            return res;
        };
        for (int i = 1; i <= n; ++i) {
            string tmp = trans(i);
            if (s.find(tmp) == string::npos) {
                return false;
            }
        }
        return true;
    }
};

