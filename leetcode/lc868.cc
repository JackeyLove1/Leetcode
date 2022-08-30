class Solution {
public:
    int binaryGap(int n) {
        int prev = -1, res = 0, idx = 0;
        while (n){
            int last = n % 2;
            n /= 2;
            if (last == 1){
                if (prev != -1){
                    res = max(res, idx - prev);
                }
                prev = idx;
            }
            ++idx;
        }
        return res;
    }
};