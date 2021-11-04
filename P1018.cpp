#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
// #include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;
using bll = __int128;

inline bll read() {
    bll X = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + ch - '0', ch = getchar();
    return X * w;
}

inline bll stobll(string &str) {
    bll res = 0;
    for (int i = 0; i < str.size(); ++i) {
        res = res * 10 + (str[i] - '0');
    }
    return res;
}

void print(bll x) {
    if (!x) return;
    if (x) print(x / 10);
    putchar(x % 10 + '0');
}

constexpr int N = 45, M = 7;
int n, m;
bll f[N][N][M], nums[N][N];
bll res;
string s;

bll solve(int l, int r, int k) {
    if (l > r) return 0;
    if (r - l + 1 <= k) return 0;
    bll &v = f[l][r][k];
    if (v != 0) return v;
    if (k == 0) return v = nums[l][r];
    for (int i = l; i < r; ++i) {
        for (int j = 0; j < k; ++j) {
            v = max(v, solve(l, i, j) * solve(i + 1, r, k - j - 1));
        }
    }
    return v;
}

int main() {
    fhj();
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i; j < s.size(); ++j) {
            auto sub = s.substr(i, j - i + 1);
            nums[i][j] = stobll(sub);
        }
    }
    res = solve(0, n - 1, m);
    print(res);
    return 0;
}