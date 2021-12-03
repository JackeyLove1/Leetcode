class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num: nums) {
            freq[num] += 1;
        }
        int ans = accumulate(nums.begin(), nums.end(), 0);
        for (int i = -100; i < 0; ++i) {
            if (freq[i]) {
                int ops = min(k, freq[i]);
                ans += (-i) * ops * 2;
                freq[i] -= ops;
                freq[-i] += ops;
                k -= ops;
                if (k == 0) {
                    break;
                }
            }
        }
        if (k > 0 && k % 2 == 1 && !freq[0]) {
            for (int i = 1; i <= 100; ++i) {
                if (freq[i]) {
                    ans -= i * 2;
                    break;
                }
            }
        }
        return ans;
    }
};
