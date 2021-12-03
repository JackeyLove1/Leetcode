// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 22, M = 35, INF = 0x3f3f3f3f;

class Solution {
public:
    bool isPalindrome(string s) {
        string tmp = "";
        for (auto &ch : s) {
            if (isdigit(ch)) tmp.push_back(ch);
            if (isalpha(ch)) tmp.push_back(tolower(ch));
        }
        // cout << tmp << endl;
        for (int i = 0, j = tmp.size() - 1; i < j; ++i, --j) {
            if (tmp[i] != tmp[j]) return false;
        }
        return true;
    }
};

int main() {
    auto s = Solution();
    cout << s.isPalindrome("A man, a plan, a canal: Panama") << endl;
}