#include <iostream>
// #include "Logger.h"

using namespace std;

#include <unordered_map>
#include <map>
#include <set>

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int convertInteger(int A, int B) {
        unsigned int n = A xor B;
        int res = 0;
        while (n) {
            n = n & (n - 1);
            ++res;
        }
        return res;
    }
};

