vector<vector<int>> flipAndInvertImage(vector<vector<int>> &A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        reverse(A[i].begin(), A[i].end());
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = abs(1 - A[i][j]);
        }
    }
    return A;
}