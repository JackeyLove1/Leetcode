#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int find(int x, vector<int> &father) {
    if (father[x] < 0)
        return x;
    else
        return father[x] = find(father[x], father);
}

void uion(int x, int y, vector<int> &father) {
    int rootx = find(x, father);
    int rooty = find(y, father);
    if (rootx == rooty)
        return ;
    father[rooty] = rootx;
}

int findCircleNum(vector<vector<int>> &M) {
    // 使用并查集
    int n = M.size();
    if (M.empty() || M[0].empty()) return 0;
    vector<int> father(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && M[i][j] == 1) {
                uion(i, j, father);
            }
        }
    }
    // 查找有几个根节点
    int cnt = 0;
    for(int i = 0;i<n;i++){
        if(father[i] == -1)
            cnt++;
    }
    return cnt;
}

int main() {
    vector<vector<int>> test1 = {{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 1}};
    cout << findCircleNum(test1) << endl;
    vector<vector<int>> test2 = {{1, 1, 0},
                                 {1, 1, 0},
                                 {0, 0, 1}};
    cout << findCircleNum(test2) << endl;
    return 0;
}