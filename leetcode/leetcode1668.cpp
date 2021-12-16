#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int res = 0;
        string repeat = word;
        while (sequence.find(repeat) != string::npos){
            ++res;
            repeat += word;
        }
        return res;
    }
};