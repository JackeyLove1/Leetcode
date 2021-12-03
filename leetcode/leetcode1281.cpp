#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

int subtractProductAndSum(int n) {
    vector<int> nums;
    while (n > 0) {
        nums.push_back(n % 10);
        n /= 10;
    }
    int sum = 0;
    int acc = 1;
    for (auto num : nums) {
        sum += num;
        acc *= num;
    }
    return acc - sum;
}