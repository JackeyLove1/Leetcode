#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

const int N = 100100, M = 400100;

int h[N], e[M], ne[M], idx;
int ans[N * 2], cnt;
bool used[M];
int din[N], dout[N];
int n, m, type;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    for (int &i = h[u]; i != -1;) {
        if (used[i]) {
            i = ne[i];
            continue;
        }
        used[i] = true;
        if (type == 1) used[i ^ 1] = true;

        int t;
        if (type == 1) {
            t = i / 2 + 1;
            if (i & 1) t = -t;
        } else t = i + 1;

        int j = e[i];
        i = ne[i];
        dfs(j);

        ans[++cnt] = t;
    }
}

int main() {
    scanf("%d", &type);
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        if (type == 1) add(b, a);
        din[b]++, dout[a]++;
    }

    if (type == 1) {
        for (int i = 1; i <= n; i++)
            if (din[i] + dout[i] & 1) {
                puts("NO");
                return 0;
            }
    } else {
        for (int i = 1; i <= n; i++)
            if (din[i] != dout[i]) {
                puts("NO");
                return 0;
            }
    }

    for (int i = 1; i <= n; i++)
        if (h[i] != -1) {
            dfs(i);
            break;
        }

    if (cnt < m) {
        puts("NO");
        return 0;
    }

    puts("YES");
    for (int i = cnt; i; i--) printf("%d ", ans[i]);
    puts("");

    return 0;
}

