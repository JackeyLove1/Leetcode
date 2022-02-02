#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

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
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        // 模拟
        for (auto &ch : firstWord) {
            ch = ch - 'a' + '0';
        }
        for (auto &ch : secondWord) {
            ch = ch - 'a' + '0';
        }
        for (auto &ch : targetWord) {
            ch = ch - 'a' + '0';
        }
        int a = stoi(firstWord);
        int b = stoi(secondWord);
        int c = stoi(targetWord);
        return a + b == c;
    }
};

int main() {
    Solution s;
    cout << s.isSumEqual("acb", "cba", "cdb") << " res: 1" << endl;
}
