class Solution {
private:
    bool gcd(int a, int b) {
        if (b == 0) return a == 1;
        return gcd(b, a % b);
    }

public:
    vector<string> simplifiedFractions(const int n) {
        vector<string> res;
        if (n == 1) return res;
        for (int k = 2; k <= n; ++k) {
            for (int i = 1; i < k; ++i) {
                if (gcd(i, k)) {
                    string s = to_string(i) + "/" + to_string(k);
                    res.emplace_back(s);
                }
            }
        }
        return res;
    }
};