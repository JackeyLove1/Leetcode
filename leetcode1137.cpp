#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
    unordered_map<int, int> cache;
public:
    Solution() {
        cache[0] = 0, cache[1] = 1, cache[2] = 1;
    }

    int tribonacci(int n) {
        if (cache.find(n) != cache.end()) return cache[n];
        int &v = cache[n];
        v = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
        return v;
    }
};

int main() {
    auto s = Solution();
    cout << s.tribonacci(4) << " res:4 " << endl;
    cout << s.tribonacci(25) << " res:1389537 " << endl;
    return 0;
}