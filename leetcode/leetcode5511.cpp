#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>

using namespace std;

bool judge(vector<vector<int> > &mat, int x, int y) {
    int sumx = 0;
    for (int i = 0; i < mat[0].size(); i++) {
        sumx += mat[x][i];
    }
    if (sumx > 1) return false;
    int sumy = 0;
    for (int i = 0; i < mat.size(); i++) {
        sumy += mat[i][y];
    }
    if (sumy > 1) return false;
    return true;
}

int numSpecial(vector<vector<int> > &mat) {
    if (mat.empty() || mat[0].empty())
        return 0;
    int res = 0;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            if(mat[i][j] == 1 && judge(mat, i, j))
                res++;
        }
    }
    return res;
}