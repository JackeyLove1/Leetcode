#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res;
    for (int i = 0; i < numRows; i++) {
        res.push_back(vector<int>(i + 1, 1));
    }
    for (int i = 0; i < numRows; i++) {
        for (int j = 1; j < i; j++) {
            res[i][j] = res[i - 1][j] + res[i - 1][j - 1];
        }
    }
    return res;
}