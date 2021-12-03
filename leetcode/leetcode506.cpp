//
// Created by Jacky on 2021/12/2.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int> &score) {
        vector<int> sorted_score = score; // deep copy
        std::sort(sorted_score.begin(), sorted_score.end(), greater<>());
        unordered_map<int, string> m;
        for (int i = 0; i < sorted_score.size(); ++i) {
            if (i == 0) m[sorted_score[i]] = "Gold Medal";
            else if (i == 1) m[sorted_score[i]] = "Silver Medal";
            else if (i == 2) m[sorted_score[i]] = "Bronze Medal";
            else {
                m[sorted_score[i]] = to_string(i + 1);
            }
        }
        vector<string> res;
        res.reserve(score.size());
        for (int &i : score) {
            res.emplace_back(m[i]);
        }
        return res;
    }
};