#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
    static constexpr int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    static constexpr int N = 16;
    int count = 0;
public:
    void dfs(int cur, int n, vector<bool> &visited) {
        if (cur == n) {
            // print(path);
            count++;
            return;
        };
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            if (nums[i] % (cur + 1) == 0 || (cur + 1) % nums[i] == 0) {
                // cout << "nums[i]: " << nums[i] << " i: " << i << endl;
                // path.push_back(nums[i]);
                visited[nums[i]] = true;
                dfs(cur + 1, n, visited);
                // path.pop_back();
                visited[nums[i]] = false;
            }
        }
    }

    int countArrangement(int n) {
        // vector<int> path;
        vector<bool> visited(N, false);
        count = 0;
        dfs(0, n, visited);
        return count;
    }
};

int main() {
    auto s = Solution();
    cout << s.countArrangement(2) << " res:2" << endl;
    cout << s.countArrangement(3) << " res:3" << endl;
    cout << s.countArrangement(15) << " res:24679" << endl;
    return 0;
}