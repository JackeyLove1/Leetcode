#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    static constexpr int N = 1e5 + 10;
    int f[N][2][3];

    int checkRecord(int n) {
        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            // 末尾加入P
            for (int j = 0; j <= 1; j++) {
                for (int k = 0; k <= 2; k++) {
                    f[i][j][0] = (f[i][j][0] + f[i - 1][j][k]) % MOD;
                }
            }
            // 末尾加入A
            for (int k = 0; k <= 2; k++) {
                f[i][1][0] = (f[i][1][0] + f[i - 1][0][k]) % MOD;
            }
            // 末尾加入L
            for (int j = 0; j <= 1; j++) {
                for (int k = 1; k <= 2; k++) {
                    f[i][j][k] = (f[i][j][k] + f[i - 1][j][k - 1]) % MOD;
                }
            }
        }
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 2; k++) {
                sum = (sum + f[n][j][k]) % MOD;
            }
        }
        return sum;
    }
};

