class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int l = 1, r = *max_element(nums.begin(), nums.end());
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int total = 0;
            for (int num: nums) {
                total += (num - 1) / mid + 1;
            }
            if (total <= threshold) {
                ans = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

