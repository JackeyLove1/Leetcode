#include<vector>
#include<iostream>

using namespace std;

void zerofy(vector<vector<int> > &matrix, int x, int y) {
    for (int i = 0; i < matrix[0].size(); i++) {
        matrix[x][i] = 0;
    }
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i][y] = 0;
    }
}

void setZeroes(vector<vector<int> > &matrix) {
    if (matrix.empty() || matrix[0].empty())
        return;
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0)
                visited[i][j] = true;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0 && visited[i][j])
                zerofy(matrix, i, j);
        }
    }
}

void print(vector<vector<int> > &m){
    for(auto nums : m){
        for (auto num : nums){
            cout<<num<<"   ";
        }
        cout<<endl;
    }
}
int main() {
    vector<vector<int> > matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    print(matrix);
    setZeroes(matrix);
    print(matrix);
}