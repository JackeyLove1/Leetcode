class Solution {
public:
    int arraySign(const vector<int> &nums) {
        int postive = 0, negtive = 0, zero = 0;
        for (const auto &num : nums) {
            if (num > 0) postive++;
            else if (num == 0) zero++;
            else negtive++;
        }
       if (zero > 0) return 0;
       if (negtive & 1) return -1;
       return 1;
    }
};