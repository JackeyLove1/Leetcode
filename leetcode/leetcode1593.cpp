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
private:
    string_view sv;
public:

    int maxUniqueSplit(string s) {
        sv = string_view(s);
        int sz = s.size();
        unordered_map<string_view, int> mp;
        int res = 1;
        std::function<void(int, int)> dfs = [&](int cur, int num) {
            if (cur >= sz) {
                res = max(res, num);
                return;
            }
            for (int len = 1; len + cur - 1 < sz; ++len) {
                auto new_sv = sv.substr(cur, len);
                if (mp[new_sv] >= 1) continue;
                mp[new_sv]++;
                dfs(cur + len, num + 1);
                mp[new_sv]--;
            }
        };
        dfs(0, 0);
        return res;
    }
};

int main() {
    Solution s;
    cout << s.maxUniqueSplit("ababccc") << " res: 5" << endl;
    cout << s.maxUniqueSplit("aba") << " res: 2" << endl;
}