// practice 2022-11-12
// author: fanhj
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr int N = 1e5, M = 1e3, INF = 0x3f3f3f3f;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

namespace str {
    int ne[N];
    char s[N], p[N];

    inline void kmp() {
        int n, m;
        cin >> n >> p + 1 >> m >> s + 1;
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j && p[i] != p[j + 1]) j = ne[j];
            if (p[i] == p[j]) ++j;
            ne[i] = j;
        }
        for (int i = 1, j = 0; i <= m; ++i) {
            while (j && s[i] != p[j + 1]) j = ne[j];
            if (s[i] == p[j + 1]) ++j;
            if (j == n) {
                cout << i - n + 1 << endl;
            }
        }
    }
}

namespace graph {

}

namespace dp {
    // count dp
    namespace countdp {
        ll f[15][15];
        int a[15], len;

        ll dp(int pos, int pre, bool lead, bool limit) {
            if (pos == -1) return 1;
            auto &v = f[pos][pre];
            if (!limit && v != -1) return v;
            ll ret = 0;
            int up = limit ? a[pos] : 9;
            for (int i = 0; i <= up; ++i) {
                if (std::abs(i - pre) < 2) continue;
                ret += dp(pos - 1, i, lead && i == 0, limit && i == up);
            }
            if (!limit && lead) v = ret;
            return ret;
        }

        ll solve(int x) {
            if (!x) return 1;
            int pos = 0;
            memset(f, -1, sizeof f);
            while (x) {
                a[pos++] = x % 10;
                x /= 10;
            }
            return dp(pos - 1, -2, 0, 1);
        }

    }
    // cat dp
    namespace catdp {
        int w[20], f[20][1 << 19], W, n, m;

        inline void catdp() {
            memset(f, 0x3f, sizeof f);
            // init
            for (int i = 1; i <= n; ++i) f[1][1 << i] = w[i];
            f[0][0] = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 0; j < (1 << n); ++j) {
                    if (f[i][j] != INF) {
                        for (int k = 1; k <= n; ++k) {
                            if (!(j & (1 << k))) {
                                if (f[i][j] + w[k] <= W) {
                                    f[i][j | (1 << k)] = std::min(f[i][j | (1 << k)], f[i][j] + w[i]);
                                } else {
                                    f[i + 1][j | (1 << k)] = std::min(f[i + 1][j | (1 << k)], w[k]);
                                }
                            }
                        }
                    }
                }
            }
            // get answer
            for (int i = 1; i <= n; ++i) {
                if (f[i][(1 << n) - 1] != INF) {
                    cout << i << endl;
                    return;
                }
            }
            return;
        }
    }

    namespace littleKing {
        int n, m;
        vector<int> state;
        int cnt[M];
        vector<int> head[M];
        ll f[N][M][M];

        inline bool check(int s) {
            for (int i = 0; i < n; ++i) {
                if ((s >> i & 1) && (s >> (i + 1) & 1)) {
                    return false;
                }
            }
            return true;
        }

        inline int count(int s) {
            int res = 0;
            for (int i = 0; i < n; ++i) {
                res += (s & (1 << i));
            }
            return res;
        }

        inline void catdp() {
            cin >> n >> m;
            for (int i = 0; i < (1 << n); ++i) {
                if (check(i)) {
                    cnt[i] = count(i);
                    state.push_back(i);
                }
            }
            for (int i = 0; i < state.size(); ++i) {
                for (int j = 0; j < state.size(); ++j) {
                    int a = state[i], b = state[j];
                    if (check(a | b) && check(a & b)) {
                        head[i].push_back(j);
                    }
                }
            }
            f[0][0][0] = 1;
            for (int i = 1; i <= n + 1; ++i) {
                for (int j = 0; j <= m; ++j) {
                    for (int a = 0; a < state.size(); ++a) {
                        for (auto b: head[state[a]]) {
                            int c = cnt[state[a]];
                            if (j >= c) {
                                f[i][j][a] += f[i - 1][j - c][b];
                            }
                        }
                    }
                }
            }
            cout << f[n + 1][m][0] << endl;
        }
    }

    namespace {
        int w[N][N];
        int f[N][1 << 20];
        int n;

        inline void hamiton() {
            memset(f, 0x3f, sizeof f);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> w[i][j];
                }
            }
            for (int i = 0; i < (1 << n); ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i & (1 << j)) {
                        for (int k = 0; k < n; ++k) {
                            if (!(i & (1 << k))) {
                                f[i][j] = std::min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
                            }
                        }
                    }
                }
            }
            cout << f[(1 << n) - 1][n - 1] << endl;
        }
    }


}

namespace base {
    namespace binary_search {
        vector<int> nums;
        int a[N], n;

        int find1(int c) {
            // <= c
            int l = 0, r = nums.size() - 1;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (nums[mid] > c) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            return l;
        }

        int find2(int c) {
            // >= c
            int l = 0, r = nums.size() - 1;
            while (l < r) {
                int mid = l + r >> 1;
                if (nums[mid] < c) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            return l;
        }
    }

    namespace {
        inline ll qsm(int a, int b, int mod) {
            ll res = 1;
            while (b) {
                if (b & 1) res = res * a % mod;
                a = 1ll * a * a % mod;
                b >>= 1;
            }
            return res;
        }

        inline ll qsc(int a, int b, int mod) {
            ll res = 0;
            while (b) {
                if (b & 1) res = (res + a) % mod;
                a = (a + a) % mod;
                b >>= 1;
            }
            return res;
        }
    }

    namespace discrete {
        vector<int> nums;
        int n;

        inline void discrete() {
            cin >> n;
            nums.assign(n, 0);
            for (int i = 0; i < n; ++i) {
                cin >> nums[i];
            }
            sort(nums.begin(), nums.end());
            nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
        }

        int find(int x) {
            return std::distance(nums.begin(), lower_bound(nums.begin(), nums.end(), x));
        }
    }

    namespace kmp2 {
        int n, m;
        int ne[N];

        inline void kmp() {
            memset(ne, 0, sizeof ne);
            char p[N], s[N];
            cin >> n >> p + 1 >> m >> s + 1;
            for (int i = 2, j = 0; i <= n; ++i) {
                while (j && p[i] != p[j + 1]) j = ne[j];
                if (p[i] == p[j + 1]) ++j;
                ne[i] = j;
            }
            for (int i = 2, j = 0; i <= m; ++i) {
                while (j && s[i] != p[j + 1]) j = ne[j];
                if (s[i] == p[j + 1]) ++j;
                if (j == n) {
                    std::cout << i - n + 1 << std::endl;
                }
            }
        }
    }

    namespace big_num{
        inline int big_mod(const int mod, const string& s){
            ll res = 0;
            for(int i = 0; i < s.size(); ++i){
                res = (res * 10 + s[i] - '0') % mod;
            }
            return res;
        }
        int primes[N], cnt, n;
        bool st[N];
        void get_primes(){
            memset(st, false, sizeof st);
            for(int i = 2; i <= n; ++i){
                if (!st[i]) primes[cnt++] = i;
                for(int j = 0; j < cnt && primes[j] * i <= n; ++j){
                    st[primes[j] * i] = true;
                    if (i % primes[j] == 0) break;
                }
            }
        }
        inline void math_block(){
            ll res = 0;
            for(int l = 1, r = 0; l <= n; l = r + 1){
                r = (n/(n/l));
                res += (r - l + 1) * (n / l);
            }
        }
    }

    
}

