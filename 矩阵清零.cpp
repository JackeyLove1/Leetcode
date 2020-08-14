#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Set matrix zero
void setZeroes(vector<vector<int>> &matrix) {
    const std::size_t m = matrix.size();
    const std::size_t n = matrix[0].size();

    vector<bool> row(m, false);
    vector<bool> col(n, false);

    // record
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0)
                row[i] = col[j] = true;
        }
    }

    // modify matrix
    for (int i = 0; i < m; i++) {
        if (row[i]) {
            for (int j = 0; j < n; j++)
                matrix[i][j] = 0;
        }
    }

    for (int j = 0; j < n; j++) {
        if (col[j]) {
            for (int i = 0; i < m; i++) {
                matrix[i][j] = 0;
            }
        }
    }
}

void print(vector<vector<int>> &matrix) {
    for (auto mxs : matrix) {
        for (auto m : mxs) {
            cout << m << "  ";
        }
        cout << endl;
    }
}


// test function
int main() {
    vector<vector<int>> matrix = {
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5}
    };
    cout << "before" << endl;
    print(matrix);
    cout << "after" << endl;
    setZeroes(matrix);
    print(matrix);
    return 0;
}