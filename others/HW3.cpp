#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
const int N = 220;
int g[N][N];
int st = 1e6, ed = -1e6;
void print(vector<int> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}
void dfs(int& maxLen,int curLen, vector<int>& visited, int point){
    // if(visited[point]) return;
    maxLen = max(maxLen, curLen);
    for(int i = st; i <= ed; i++){
        if(!visited[i] && g[point][i] != 0){
            curLen += g[point][i];
            cout << "curLen: " << curLen << endl;
            maxLen = max(maxLen, curLen);
            visited[i] = true;
            dfs(maxLen, curLen, visited, i);
            visited[i] = false;
            curLen -= g[point][i];
        }
    }
}

int main() {
    string s;
    getline(cin, s);
    vector<int> nums;
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) continue;
        int tmp = s[i] - '0';
        while (i + 1 < s.size() && isdigit(s[i + 1])) {
            tmp = tmp * 10 + s[++i] - '0';
        }
        nums.push_back(tmp);
    }
    // print(nums);
    memset(g, 0, sizeof g);
    int res = 0;
    while (nums.size()) {
        int w = nums.back();
        nums.pop_back();
        int b = nums.back();
        nums.pop_back();
        int a = nums.back();
        nums.pop_back();
        g[a][b] = w;
        res = max(res, w);
        ed = max(ed, max(a, b));
        st = min(st, min(a, b));
        cout << a << " " << b << " " << w << endl;
    }
    cout << "st: " << st << " ed: " << ed << endl;
    for(int i = st; i <= ed; i++){
        vector<int>visited(N, false);
        int curLen = 0;
        dfs(res, curLen, visited, i);
    }
    cout << res << endl;
    return 0;
}