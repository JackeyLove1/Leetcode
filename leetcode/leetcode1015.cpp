class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if ((k % 2 == 0) || (k % 5 == 0))
        {
            return -1;
        }

        int temp = 1;
        int cnt = 1;
        while (temp % k != 0)
        {
            temp %= k;
            temp = temp * 10 + 1;
            ++cnt;
        }

        return cnt;
    }
};