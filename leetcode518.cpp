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
    int change(int amount, vector<int> &coins) {
        int n = coins.size();
        vector<vector<int>> f(n + 2, vector<int>(amount + 1, 0));
        coins.insert(coins.begin(), 0);
        for (int i = 0; i <= n; i++) f[i][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= amount; j++) {
                f[i][j] = f[i - 1][j];
                for (int k = 1; k * coins[i] <= j; k++) {
                    f[i][j] += f[i - 1][j - k * coins[i]];
                }
            }
        }
        return f[n][amount];
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {1, 2, 5};
    cout << s.change(5, nums) << " res: 4" << endl;
    return 0;
}

/*
// dfs 解法
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
private:
    using PII = pair<int, int>;
    map<PII, int> cache;
    int count = 0;
public:
    void dfs(int cur, int partSum, int amount, vector<int> &coins) {
        if (cur == coins.size()) {
            if (partSum == amount) {
                count++;
            }
            return;
        }
        if (partSum > amount) return;
        for (int k = 0; k * coins[cur] + partSum <= amount; k++) {
            dfs(cur + 1, partSum + k * coins[cur], amount, coins);
        }
    }

    int change(int amount, vector<int> &coins) {
        dfs(0, 0, amount, coins);
        return count;
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {1, 2, 5};
    cout << s.change(5, nums) << " res: 4" << endl;
    return 0;
}
*/

/*----------------------------------------------------------------
// 记忆化搜索DFS
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
private:
    using PII = pair<int, int>;
    map<PII, int> cache;
    // int count = 0;
public:
    int solve(int cur, int partSum, int amount, vector<int> &coins) {
        PII p = {cur, partSum};
        if (cache.count(p)) return cache[p];
        cache[p] = 0;
        int &v = cache[p];
        if (cur == coins.size()) {
            if (partSum == amount) {
                return v = 1;
            }
            return 0;
        }
        if (partSum > amount) return 0;
        for (int k = 0; k * coins[cur] + partSum <= amount; k++) {
            v += solve(cur + 1, partSum + k * coins[cur], amount, coins);
        }
        return v;
    }

    int change(int amount, vector<int> &coins) {
        return solve(0, 0, amount, coins);
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {1, 2, 5};
    cout << s.change(5, nums) << " res: 4" << endl;
    return 0;
}
*/