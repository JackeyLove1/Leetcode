class Solution {
public:
    bool check(vector<int> &s, int len, int k) {
        for (int l = 1, r = l + len - 1; r < s.size(); ++l, ++r) {
            // cout <<"l: " << l << " r: " << r << " s: " << s[r] - s[l - 1] << endl;
            if (s[r] - s[l - 1] >= k) return true;
        }
        return false;
    }

    int shortestSubarray(vector<int> &nums, int k) {
        const int n = nums.size();
        vector<int> s(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + nums[i - 1];
        }
        int l = 1, r = nums.size();
        // cout <<"l: " << l << " r: " << r << " s: " << s[r] - s[l - 1] << endl;
        while (l < r) {
            int mid = l + r >> 1;
            if (check(s, mid, k)) r = mid;
            else l = mid + 1;
        }
        if (check(s, r, k)) return r;
        return -1;
    }
};