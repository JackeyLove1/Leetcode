#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}


const int N = 55, mod = 1e9 + 7;

int n, m;
string str;
int ne[N];
int f[N][N];

int main() {
    fhj();
    cin >> n >> str;
    str = " " + str; // 使得str下标从1开始
    m = str.size() - 1;
    // get str kmp
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && str[i] != str[j + 1]) j = ne[j];
        if (str[i] == str[j + 1]) j++;
        ne[i] = j; // 得到最长匹配前缀
    }
    // dp
    f[0][0] = 1; // init
    for (int i = 0; i < n; ++i) { // 枚举构造串
        for (int j = 0; j < m; ++j) { // 枚举匹配串
            for (char k = 'a'; k <= 'z'; ++k) { // 枚举下一个位置的匹配
                int u = j; // 开始匹配
                while (u && k != str[u + 1]) u = ne[u];
                if (k == str[u + 1]) u++; // 匹配成功 j -> u
                if (u < m) f[i + 1][u] = (f[i][j] + f[i + 1][u]) % mod;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < m; ++i) res = (res + f[n][i]) % mod;
    cout << res << endl;
    return 0;
}