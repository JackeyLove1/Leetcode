#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}

constexpr int N = 6;

char g[N][N], bg[N][N];
// 上下左右四种状态
int dx[] = {-1, 0, 1, 0, 0}, dy[] = {0, 1, 0, -1, 0};

// 按一下第x行第y列的开关
void turn(int x, int y) {
    for (int i = 0; i < 5; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= 5 || b < 0 || b >= 5) continue;
        g[a][b] ^= 1; // 翻转
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 5; i++) cin >> bg[i];
        int res = 10;
        for (int op = 0; op < 32; op++) { // 2 ^ 5 = 32, 状态枚举
            int cnt = 0;
            memcpy(g, bg, sizeof g);
            // 操作第一行开关
            for (int i = 0; i < 5; i++) { //
                if (op >> i & 1) {
                    turn(0, i);
                    cnt++;
                }
            }
            // 递推1-4行的状态
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 5; j++) {
                    if (g[i][j] == '0') {
                        turn(i + 1, j);
                        cnt++;
                    }
                }
            }
            // 检查最后一行灯是否全亮
            bool success = true;
            for (int i = 0; i < 5; i++) {
                if (g[4][i] == '0') {
                    success = false;
                }
            }
            if (success && res > cnt) res = cnt;
        }
        if (res > 6) res = -1;
        cout << res << endl;
    }
    return 0;
}