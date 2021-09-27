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

constexpr int debug = 1;
constexpr int N = 1010;
int g[N][N];

inline int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void gprint(int n, int x, int y) {
    if (n == 1) {
        g[x][y] = 1;
        return;
    }
    int len = power(3, n - 2);
    gprint(n - 1, x, y);
    gprint(n - 1, x + 2 * len, y);
    gprint(n - 1, x + len, y + len);
    gprint(n - 1, x, y + 2 * len);
    gprint(n - 1, x + 2 * len, y + 2 * len);
}

int n;

int main() {
    while (cin >> n && n != -1) {
        gprint(n, 1, 1);
        for (int i = 1; i <= power(3, n - 1); i++) {
            for (int j = 1; j <= power(3, n - 1); j++)
                if (g[i][j])
                    cout << "X";
                else
                    cout << " ";
            cout << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}