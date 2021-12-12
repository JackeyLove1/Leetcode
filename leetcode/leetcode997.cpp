#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int findJudge(int n, vector<vector<int>> &trust) {
        int sz = n;
        if(trust.empty()) return n > 1 ? -1 : 1;
        vector<int> person(sz + 1, 0);
        vector<bool> trust_sb(sz + 1, false);
        vector<int> candidates;
        for (auto &vec : trust) {
            trust_sb[vec[0]] = true;
            if (++person[vec[1]] == sz - 1) {
                candidates.push_back(vec[1]);
            }
        }
        for (auto &candidate : candidates) {
            if (!trust_sb[candidate])
                return candidate;
        }
        return -1;
    }
};

