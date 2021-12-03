#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    string reverseVowels(string s) {
        if (s.empty()) return "";
        set<char> set1 = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int l = -1, r = s.size();
        while (l < r) {
            do l++; while (!set1.count(s[l]) && l < r);
            do r--; while (!set1.count(s[r]) && l < r);
            if (l < r) swap(s[l], s[r]);
        }
        return s;
    }
};

int main() {
    auto s = Solution();
    cout << s.reverseVowels(" ") << " res: " << endl;
    return 0;
}