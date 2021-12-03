#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int debug = 0;

    string findDifferentBinaryString(vector<string> &nums) {
        int n = nums[0].size();
        if (debug) cout << "n: " << n << endl;
        unordered_set<string> s;
        for (auto &num : nums) {
            s.insert(num);
        }
        auto f = [&](int x) -> string {
            string tmp;
            if (debug) cout << "x: " << x << endl;
            while (x) {
                tmp = (x & 1) ? ('1' + tmp) : ('0' + tmp);
                x >>= 1;
            }
            for (int i = 0, l = tmp.size(); l + i < n; i++) {
                tmp = '0' + tmp;
            }
            if (debug) cout << tmp << endl;
            return tmp;
        };

        for (int i = 0; i < 1 << n; i++) {
            string str(move(f(i)));
            if (!s.count(str)) {
                return str;
            }
        }
        return "";
    }
};

int main() {
    auto s = Solution();
    vector<string> nums = {"00", "10"};
    cout << s.findDifferentBinaryString(nums) << endl;
    return 0;
}