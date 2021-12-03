int maxSumSlidingWindow(vector<int> &nums, int k) {
    int i = 0, res = 0, tmp = 0;
    for (; i < k; i++) {
        tmp += nums[i];
    }
    res = tmp;
    size_t size = nums.size();
    for (; i < size - k; i++) {
        tmp = tmp - nums[i] + nums[i + k - 1];
        res = max(res, tmp);
    }
    return res;
}