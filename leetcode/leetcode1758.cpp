#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        string sZero, sOne;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                sZero.push_back('0');
                sOne.push_back('1');
            } else {
                sZero.push_back('1');
                sOne.push_back('0');
            }
        }
        int disZero = 0, disOne = 0;
        for (int i = 0; i < n; ++i) {
            if (sZero[i] != s[i]) ++disZero;
            if (sOne[i] != s[i]) ++disOne;
        }
        return min(disOne, disZero);
    }
};