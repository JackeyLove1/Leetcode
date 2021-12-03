#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>
#include <stdlib.h>

using namespace std;

// 使用回溯的方法
// turn = 1 first
// turn = -1 second
int backtrace(vector<int> &nums, int start, int end, int turn) {
    if (start == end) return nums[start] * turn;
    int startScore = nums[start] * turn + backtrace(nums, start + 1, end, -turn);
    int endScore = nums[end] * turn + backtrace(nums, start, end - 1, -turn);
    return max(startScore * turn, endScore * turn) * turn;
}

bool PredictTheWinner(vector<int> &nums) {
    return backtrace(nums, 0, nums.size() - 1, 1) >= 0;
}