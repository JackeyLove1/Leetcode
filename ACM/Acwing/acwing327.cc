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

typedef long long LL;

const int N = 15, M = 1 << 12, K = 110;
constexpr int mod = 1e8;
int n, m;
vector<int> state;
int cnt[M];
vector<int> head[M];
LL f[N][M];
int w[N];

bool check(int state) {
    for (int i = 0; i + 1 < m; i++)
        if ((state >> i & 1) && (state >> i + 1 & 1))
            return false;
    return true;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int t;
            cin >> t;
            w[i] += !t * (1 << j);
        }
    }
    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) {
            state.push_back(i);
        }
    }
    for (int i = 0; i < state.size(); i++)
        for (int j = 0; j < state.size(); j++) {
            int a = state[i], b = state[j];
            if ((a & b) == 0)
                head[i].push_back(j);
        }

    f[0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < state.size(); ++j) {
            if (!(state[j] & w[i])) {
                for (const auto k: head[j]) {
                    f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                }
            }
        }
    }

    cout << f[n + 1][0] << endl;

    return 0;
}
