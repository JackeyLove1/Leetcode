#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> ransom_map;
        unordered_map<char, int> mag_map;
        for (auto &ch : ransomNote) {
            ++ransom_map[ch];
        }
        for (auto &ch : magazine) {
            ++mag_map[ch];
        }
        for (auto&[k, v] : ransom_map) {
            if (mag_map[k] < v) {
                return false;
            }
        }
        return true;
    }
};