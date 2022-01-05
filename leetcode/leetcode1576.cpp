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
    string modifyString(string s) {
        srand(time(nullptr));
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '?') {
                s[i] = 'a' + rand() % 26;
                while ((i > 0 && s[i] == s[i - 1]) || (i + 1 < s.size() && s[i] == s[i + 1])) {
                    s[i] = 'a' + rand() % 26;
                }
            }
        }
        return s;
    }
};