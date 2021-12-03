#include <iostream>
#include <vector>

using namespace std;

bool check(char ch, bool used[]) {
    if (ch == '.') return true;
    if (used[ch - '1']) return false;
    used[ch - '1'] = true;
    return true;
}

bool isValidSudoku(vector<vector<char>> &board) {
    bool used[9];

    // 检查行和列
    for (int i = 0; i < 9; i++) {
        // 检查行
        fill(used, used + 9, false);
        for (int j = 0; j < 9; j++) {
            if (!check(board[i][j], used))
                return false;
        }
        // 检查列
        fill(used, used + 9, false);
        for (int j = 0; j < 9; j++) {
            if (!check(board[j][i], used))
                return false;
        }
    }

    // 检查九宫格
    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            fill(used, used + 9, false);
            for (int i = col * 3; i < col * 3 + 3; i++) {
                for (int j = row * 3; j < row * 3 + 3; j++) {
                    // cout<<board[i][j]<<" ";
                    if (!check(board[i][j], used))
                        return false;
                }
            }
            // cout<<endl;
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    cout << ((isValidSudoku(board) == true) ? 1 : 0) << endl;
    return 0;
}
