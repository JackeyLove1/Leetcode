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
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) ans = ans * 10 + c - '0', c = getchar();
    return ans;
}

using ll = long long;
#define rint read<int>()
#define rll read<ll>()

constexpr int N = 1e6 + 100;
int f[N], g[N];
char nums[N];

int main() {
    int n = rint;
    scanf("%s", nums);
    // memset(f, 0x3f, sizeof f);
    // memset(g, 0x3f, sizeof g);
    f[0] = (nums[0] == 'B'), g[0] = (nums[0] == 'A');
    for (int i = 1; i < n; ++i) {
        if (nums[i] == 'A') {
            f[i] = f[i - 1];
            g[i] = std::min(f[i - 1] + 1, g[i - 1] + 1);
        } else {
            g[i] = g[i - 1];
            f[i] = std::min(f[i - 1] + 1, g[i - 1] + 1);
        }
    }
    cout << f[n - 1] << endl;
    return 0;
}