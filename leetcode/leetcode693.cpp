#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;

int q[N];

bool hasAlternatingBits(int n) {
    vector<int> nums;
    while (n) {
        nums.push_back(n % 2);
        n >>= 1;
    }
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) {
            return false;
        }
    }
    return true;
}