#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        unordered_map<char, vector<int>> char_index;
        for (int i = 0; i < s.size(); ++i) {
            char_index[s[i]].push_back(i);
        }
        int max_res = -1;
        for (auto&[_, vec] : char_index) {
            if (vec.size() < 2) continue;
            max_res = max(max_res, vec.back() - vec.front() - 1);
        }
        return max_res;
    }
};