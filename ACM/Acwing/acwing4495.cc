#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 1e5 + 100;
int n, m;
int w[N];

int main() {
    fhj();
    cin >> n >> m;
    int zero = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        zero += static_cast<int>(w[i] == 0);
    }
    if (zero == n) {
        for (int i = 0; i < m; ++i) {
            cout << 0 << endl;
        }
    }
    sort(w, w + n);
    int cnt = 0, p = 0;
    while (p < n && m) {
        while (w[p] == cnt && p < n) ++p;
        if(p == n) break;
        cout << w[p] - cnt << endl;
        // cout << "w[p]: " << w[p] <<" cnt: " << cnt <<" ";
        cnt += w[p] - cnt;
        --m, ++p;
        // cout <<"p: " << p <<" cnt: " << cnt << endl;
    }
    while (m--){
        cout << 0 << endl;
    }
    return 0;
}