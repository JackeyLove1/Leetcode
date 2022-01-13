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

class Solution {
public:
    bool checkString(const string &s) {
        int indexA = -1, indexB = -1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'b') {
                indexB = i;
                break;
            }
        }
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == 'a') {
                indexA = i;
                break;
            }
        }
        // cout << "A: " << indexA << endl;
        // cout << "B: " << indexB << endl;
        return (indexA == -1) || (indexB == -1) || (indexA < indexB);
    }
};

int main() {
    Solution s;
    cout << s.checkString("aaabbb") << endl;
}