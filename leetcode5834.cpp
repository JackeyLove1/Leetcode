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
    int minTimeToType(string word) {
        if (word.size() == 1) return 1;
        auto f = [](char a, char b) -> int {
            // cout << "a: " << a << " b: " << b << " res:" << min(26 - abs(a - b), abs(a - b)) << endl;
            return min(26 - abs(a - b), abs(a - b));
        };
        char target = 'a';
        int res = 0;
        // int res = target == 'a' ? 1 : 2;
        for (int i = 0; i < word.size(); i++) {
            res += f(target, word[i]) + 1;
            target = word[i];
        }
        return res;
    }
};

int main() {
    // cout << min(26 - abs('z' - 'a'), abs('z' - 'a')) << endl;
    auto s = Solution();
    cout << s.minTimeToType("pdy") << " res: 31" << endl;
}