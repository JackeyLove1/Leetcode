#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100;
bool st[N];
int n;

void dfs(int step) {
    if (step == n + 1) {
        for (int i = 1; i <= n; ++i){
            if (st[i]) cout << i << " ";
        }
        cout << endl;
        return ;
    }
    dfs(step + 1);
    st[step] = true;
    dfs(step + 1);
    st[step] = false;
}

int main() {
    cin >> n;
    memset(st, false, sizeof st);
    dfs(1);
    return 0;
}