int findDuplicate(vector<int> &nums) {
    unordered_map<int, int> hash;
    for (auto num : nums) {
        if (hash.find(num) == hash.end())
            hash[num] = 1;
        else
            return num;
    }
    return -1;
}