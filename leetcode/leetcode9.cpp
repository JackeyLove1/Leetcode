#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    vector<int> nums;
    while (x) {
        nums.push_back(x % 10);
        x /= 10;
    }
    for (int i = 0, j = nums.size() - 1; i < j; i++, j--) {
        if (nums[i] != nums[j])
            return false;
    }
    return true;
}