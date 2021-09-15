#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

int n;

void print(vector<int> &nums) {
    for (auto &num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

void dfs(int cur, int last, vector<int> &path) {
    if (cur < 0) return;
    if (cur == 0) {
        for (int i = 0; i < path.size() - 1; ++i) {
            cout << path[i] << "+";
        }
        cout << path.back();
        cout << endl;
        return;
    }
    for (int i = 1; i < n; ++i) {
        if (i < last || i > cur) continue;
        path.push_back(i);
        // print(path);
        dfs(cur - i, i, path);
        path.pop_back();
    }
}

int main() {
    cin >> n;
    vector<int> path;
    dfs(n, 0, path);
    return 0;
}