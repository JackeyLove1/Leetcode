// #pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e7 + 100, M = 65, INF = 0x3f3f3f3f;
using ll  = long long;
ll f[20];
int main(){
    int n;
    cin >> n;
    f[0] = 1;
    for(int i = 1; i <= n; ++i){
        f[i] = f[i-1] * (4 * i - 2) / (i + 1);
    }
    cout << f[n] << endl;
    return 0;
}