void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            swap(matrix[i][j], matrix[n - 1 - i][j]);
        }
    }
    for (int l = 0; l < n; l++) {
        for (int i = 0; i < l; i++) {
            swap(matrix[i][l], matrix[l][i]);
        }
    }
}

void print(vector<vector<int>> &nums) {
    for (auto vec : nums) {
        for (auto num : vec) {
            cout << num << "  ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> matrix = {{5,  1,  9,  11},
                                  {2,  4,  8,  10},
                                  {13, 3,  6,  7},
                                  {15, 14, 12, 16}};
    rotate(matrix);
    print(matrix);
}