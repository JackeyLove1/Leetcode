#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

template<typename T>
inline T read() {
    T ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

using ll = long long;
#define rint read<int>()
#define rll read<ll>()
constexpr int N = 330;
int nums[N], f[N][N];

int main() {
    int n = rint;
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) {
        nums[i] = rint;
        f[i][i] = 0;
        nums[i] += nums[i - 1];
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            int add = nums[j] - nums[i - 1];
            for (int k = i; k < j; ++k) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j] + add);
            }
        }
    }
    cout << f[1][n] << endl;
    return 0;
}