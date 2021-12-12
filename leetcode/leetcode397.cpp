#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int integerReplacement(int n) {
        // 使用bfs解法或者记忆化搜索
        auto start = static_cast<long long>(n);
        queue<long long> q;
        q.push(start);
        int step = 0;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                auto t = q.front();
                if (t == 1) return step;
                q.pop();
                if (t % 2 == 0) {
                    q.push(t / 2);
                } else {
                    q.push(t + 1);
                    q.push(t - 1);
                }
            }
            ++step;
        }
        return -1;
    }
};

int main() {
    Solution s;
    cout << s.integerReplacement(2147483647) << " res: ?" << endl;
}