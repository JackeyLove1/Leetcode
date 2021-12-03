#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>
#include <numeric>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    // 经典状态压缩DP，三进制形式
    int colorTheGrid(int m, int n) {
        const int MOD = 1e9 + 7;
        int smax = int(pow(3, m));
        vector<vector<int>> f(n + 10, vector<int>(smax, 0));

        function<bool(int)> checkS = [m](int s) -> bool {
            // 检查是否有两个连续的状态
            int last = -1;
            for(int i = 0; i < m; i++){
                if (s % 3 == last) return false;
                last = s % 3;
                s /= 3;
            }
            return true;
        };

        function<bool(int, int)> checkXY = [m](int x, int y) -> bool {
            for (int i = 0; i < m; i++) {
                if (x % 3 == y % 3) return false;
                x /= 3, y /= 3;
            }
            return true;
        };

        // init
        vector<int> states;
        for (int i = 0; i < smax; i++) {
            if (checkS(i)) {
                f[0][i] = 1;
                states.push_back(i);
            }
        }

        for (int i = 1; i < n; i++) {
            for (auto &x : states) {
                for (auto &y : states) {
                    if (checkXY(x, y)) {
                        f[i][x] = (f[i][x] + f[i - 1][y]) % MOD;
                    }
                }
            }
        }

        int sum = 0;
        for (auto &state : states) {
            sum = (sum + f[n - 1][state]) % MOD;
        }

        return sum;
    }
};

int main() {
    auto s = Solution();
    cout << s.colorTheGrid(1, 1) << " res:3" << endl;
    cout << s.colorTheGrid(1, 2) << " res:6" << endl;
    cout << s.colorTheGrid(5, 5) << " res:580986" << endl;
    return 0;
}