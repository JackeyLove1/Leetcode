#include <iostream>

using namespace std;

#include <unordered_set>

class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        unordered_set<int> s = {2, 3, 5, 7, 11, 13, 17, 19};
        std::function<bool(int)> check = [&](int x) -> bool {
            int sum = 0;
            while (x) {
                if (x & 1) ++sum;
                x >>= 1;
            }
            return s.count(sum) > 0;
        };
        int res = 0;
        for (int i = left; i <= right; ++i) {
            if (check(i)) ++res;
        }
        return res;
    }
};