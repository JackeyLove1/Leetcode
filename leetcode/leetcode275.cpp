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

template<typename T>
inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int hIndex(vector<int> &citations) {
        int h = 0;
        sort(citations.begin(), citations.end(), greater<>());
        for (int citation : citations) {
            if (citation >= h + 1) {
                ++h;
            } else {
                break;
            }
        }
        return h;
    }
};

int main() {
    vector<int> vec({0, 1, 3, 5, 6});
    Solution s;
    cout << s.hIndex(vec) << endl;
    vector<int> vec2({1, 1});
    cout << s.hIndex(vec2) << endl;
    return 0;
}