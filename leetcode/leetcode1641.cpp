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
private:
    int f[55][5];

    /*
    unordered_map<char, int> mp = {{'a', 4},
                                   {'e', 3},
                                   {'i', 2},
                                   {'o', 1},
                                   {'u', 0}};
    */
    int solve(int pos, int pre) {
        if (pos == -1) return 1;
        int &v = f[pos][pre];
        if (v != -1) return v;
        v = 0;
        for (int i = pre; i >= 0; --i) {
            v += solve(pos - 1, i);
        }
        return v;
    }

public:
    int countVowelStrings(int n) {
        // memory search
        memset(f, -1, sizeof f);
        int res = 0;
        for (int i = 0; i < 5; ++i) {
            res += solve(n - 2, i);
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.countVowelStrings(1) << " res: 5" << endl;
    cout << s.countVowelStrings(2) << " res: 15" << endl;
    cout << s.countVowelStrings(33) << " res: 66045" << endl;
}