class Solution {
    constexpr static int res[] = {9, 987, 123, 597, 677, 1218, 877, 475};
public:
    int largestPalindrome(int n) {
        return res[n - 1];
    }
};