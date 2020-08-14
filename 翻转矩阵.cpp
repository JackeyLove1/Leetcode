#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<vector<int>> &matrix) {
    for (auto mxs : matrix) {
        for (auto m : mxs) {
            cout << m << "  ";
        }
        cout << endl;
    }
}

void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();
    // 沿对角线反转
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            swap(matrix[i][j], matrix[n - i - 1][n - j - 1]);
        }
    }

    // 沿水平中线反转
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            swap(matrix[i][j], matrix[n - i - 1][j]);
        }
    }
}

// test function
int main() {
    vector<vector<int>> matrix = {{1, 2},
                                  {3, 4}};
    cout << "before rotating" << endl;
    print(matrix);
    rotate(matrix);
    cout << "after rotating" << endl;
    print(matrix);
    return 0;
}