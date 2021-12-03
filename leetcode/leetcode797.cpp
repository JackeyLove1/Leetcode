#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph) {
        int n = graph.size();
        vector<vector<int>> res;
        vector<int> path = {0};
        function<void(int)> dfs = [&](int cur) -> void {
            if (cur == n - 1) {
                res.push_back(path);
                return;
            }
            for (auto &p : graph[cur]) {
                path.push_back(p);
                dfs(p);
                path.pop_back();
            }
        };

        dfs(0);
        return res;
    }
};