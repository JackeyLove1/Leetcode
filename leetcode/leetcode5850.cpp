#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int findGCD(vector<int> &nums) {
        int maxN = *max_element(nums.begin(), nums.end());
        int minN = *min_element(nums.begin(), nums.end());

        function<int(int, int)> gcd = [](int a, int b) -> int {
            for (int i = min(a, b); i >= 0; i--) {
                if (a % i == 0 && b % i == 0) {
                    return i;
                }
            }
            return 1;
        };

        return gcd(minN, maxN);
    }
};
