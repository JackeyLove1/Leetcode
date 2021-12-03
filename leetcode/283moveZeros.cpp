void moveZeroes(vector<int> &nums) {
    vector<int> tmp;
    int zeros = 0;
    for (auto num : nums) {
        if (num == 0)
            zeros++;
        else
            tmp.push_back(num);
    }
    while (zeros-- > 0) {
        tmp.push_back(0);
    }
    nums.clear();
    nums.assign(tmp.begin(), tmp.end());
}