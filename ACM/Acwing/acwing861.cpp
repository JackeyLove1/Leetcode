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

constexpr int N = 510, M = 1e5 + 100;
int e[M], ne[M], h[N], idx;
int st[N];
int match[N];
int n1, n2, m;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool find(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]){
            st[j] = true;
            if (!match[j] || find(match[j])){
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    fhj();
    cin >> n1 >> n2 >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    int res = 0;
    for (int i = 1; i <= n1; ++i) {
        memset(st, 0, sizeof st);
        if (find(i)) {
            ++res;
        }
    }
    cout << res << endl;
}