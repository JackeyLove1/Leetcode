// Author: Jacky
// Time: 2021-09-25
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int debug = 0;

constexpr int N = 6;
int back[N][N], g[N][N];

inline void print() {
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            cout << back[i][j] << ' ';
        }
        cout << endl;
    }
}

inline void turn(int x, int y) {
    for (int i = 1; i <= 4; ++i) {
        back[x][i] ^= 1;
        back[i][y] ^= 1;
    }
    back[x][y] ^= 1;
}

static int res = 1e6;
unordered_map<int, vector<vector<PII>>> m;

int main() {
    fhj();
    char ch;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            cin >> ch;
            g[i][j] = ch == '+' ? 0 : 1;
        }
    }
    for (int state = 0; state < (1 << 16); ++state) {
        memcpy(back, g, sizeof g);
        vector<PII> path;
        int cur = 0;
        for (int k = 0; k < 16; ++k) {
            if (state & (1 << k)) {
                int x = k / 4, y = k % 4;
                ++x, ++y;
                path.emplace_back(x, y);
                ++cur;
                turn(x, y);
            }
        }
        if (cur > res) continue;
        auto flag = true;
        for (int i = 1; i <= 4; ++i) {
            for (int j = 1; j <= 4; ++j) {
                if (!back[i][j]) flag = false;
            }
        }
        if (!flag) continue;
        m[cur].emplace_back(path);
        res = res > cur ? cur : res;
        if (debug) {
            cout << "after state, the step is : " << cur << endl;
            print();
        }
    }
    cout << res << endl;
    for (auto &vec : m[res]) {
        for (auto &v : vec) {
            cout << v.first << ' ' << v.second << endl;
        }
    }
    return 0;
}