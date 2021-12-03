//
// Created by Jacky on 2021/12/1.
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
    vector<string> stringMatching(vector<string> &words) {
        vector<string> res;
        for (size_t i = 0; i < words.size(); ++i) {
            for (size_t j = 0; j < words.size(); ++j) {
                if (i == j) continue;
                auto n = words[j].find(words[i]);
                if (n != std::string::npos) {
                    res.push_back(words[i]);
                    break;
                }
            }
        }
        return res;
    }
};