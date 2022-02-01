#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    int get(int n) {
        int sq = static_cast<int>(sqrt(n));
        int cnt = 0, sum = 0;
        if (n == sq * sq) return 0;
        for (int i = 1; i <= sq; ++i) {
            if (n % i == 0) {
                cnt += 2;
                sum += i + n / i;
            }
        }
        // cout << "n: " << n << " cnt: " << cnt << " sum: " << sum << endl;
        return cnt == 4 ? sum : 0;
    }

public:
    int sumFourDivisors(const vector<int> &nums) {
        int sum = 0;
        for (const int num : nums) {
            sum += get(num);
        }
        return sum;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << s.sumFourDivisors(nums) << " res: 45" << endl;
    return 0;
}