#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

int minFallingPathSum(vector<vector<int> > &A) {
    if (A.empty() || A[0].empty()) return 0;
    int m = A.size();
    int n = A[0].size();
    for (int i = 1; i < m; i++) { // 从第一列开始
        for (int j = 0; j < n; j++) {
            if(j == 0)
                A[i][j] += min(A[i-1][j], A[i-1][j+1]);
            else if (j == n-1)
                A[i][j] += min(A[i-1][j-1], A[i-1][j]);
            else
                A[i][j] += min(A[i-1][j-1], min(A[i-1][j], A[i-1][j+1]));
        }
    }
    return *min_element(A[m-1].begin(), A[m-1].end());
}