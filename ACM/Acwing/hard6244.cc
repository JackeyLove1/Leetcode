#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static constexpr int N = 110, MOD = 1e9 + 7;
    using ll = long long;
    using p = std::tuple<int, int, int>;
    map<p, int> f;

    inline static auto isPrime(char s) {
        return s == '2' || s == '3' || s == '5' || s == '7';
    }

    int beautifulPartitions(string s, int k, int minLength) {
        if (s.empty() || !isPrime(s.front()) || isPrime(s.back())) return 0;
        // int f[N][N][N];
        // memset(f, -1, sizeof f);
        f.clear();
        std::function<int(int, int, int)> dp = [&](int i, int j, int k) -> int {
            if (j - i + 1 < minLength * k) return 0;
            if (!isPrime(s[i]) || isPrime(s[j])) return 0;
            if (k == 1) return 1;
            auto tp = std::make_tuple(i, j, k);
            if (f.count(tp)) return f[tp];
            f[tp] = 0;
            for (int mid = i + minLength - 1; mid + minLength - 1 <= j; ++mid) {
                for (int subk = 1; subk < k; ++subk) {
                    f[tp] = (f[tp] + dp(i, mid, subk) * dp(mid + 1, j, k - subk) % MOD) % MOD;
                }
            }
            // cout << "i: " << i << " j: " << j << " k: " << k << " res: " << f[tp] << endl;
            return f[tp];
        };
        auto res = dp(0, s.size() - 1, k) % MOD;
        return k == 1 ? res : res / 2;
    }
};

int main() {
    Solution s{};
    cout << s.beautifulPartitions("23542185131", 3, 2) << " res: 3" << endl;
    cout << s.beautifulPartitions("23542185131", 3, 3) << " res: 1" << endl;
    cout << s.beautifulPartitions("3312958", 3, 1) << " res: 1" << endl;
    cout << s.beautifulPartitions("242538614532395749146912679859", 1, 6) << " res: 1" << endl;
    return 0;
}