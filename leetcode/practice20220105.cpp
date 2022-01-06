#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 1e6 + 10;

namespace trie {
    int son[N][26], cnt[N], idx = 0;

    void insert(const string &str) {
        int p = 0;
        for (const char ch : str) {
            int u = ch - 'a';
            if (!son[p][u]) son[p][u] = idx++;
            p = son[p][u];
        }
        cnt[p]++;
    }

    int query(const string &str) {
        int p = 0;
        for (const char ch : str) {
            int u = ch - 'a';
            if (!son[p][u]) return 0;
            p = son[p][u];
        }
        return cnt[p];
    }
}

namespace trie01 {
    int a[N], son[N * 31][2];
    int idx = 0, n;

    void insert(int x) {
        int p = 0;
        for (int i = 31; i >= 0; --i) {
            int u = x & (1 << i);
            if (!son[p][u]) son[p][u] = idx++;
            p = son[p][u];
        }
    }

    int query(int x) {
        int p = 0, ret = 0;
        for (int i = 31; i >= 0; --i) {
            int u = x & (1 << i);
            if (!son[p][u]) {
                p = son[p][u];
                ret = ret * 2 + u;
            } else {
                p = son[p][!u];
                ret = ret * 2 + !u;
            }
        }
        ret = ret ^ x;
        return ret;
    }
}

namespace AC_simple {
    // trie + KMP
    int tr[N][26], cnt[N], idx = 0;
    int fail[N];

    void insert(const string &str) {
        int p = 0;
        for (auto ch : str) {
            int u = ch - 'a';
            if (!tr[p][u]) tr[p][u] = ++idx;
            p = tr[p][u];
        }
        cnt[p]++;
    }

    queue<int> q;

    void build() {
        for (int i = 0; i < 26; ++i) {
            if (tr[0][i]) q.push(tr[0][i]);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    q.push(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query(const string &str) {
        int u = 0, res = 0;
        for (auto ch : str) {
            u = tr[u][ch - 'a'];
            for (int j = u; j && cnt[j] != -1; j = fail[j]) {
                res += cnt[j], cnt[j] = -1;
            }
        }
        return res;
    }
}

int main(){
    
}