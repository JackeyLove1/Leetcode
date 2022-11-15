#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100;
int primes[N], cnt{0};
bool vis[N];
std::set<int> s;
inline void init(){
    const int n = 1e5 + 1;
    memset(vis, false, sizeof vis);
    for(int i = 2; i <= n; ++i){
        if (!vis[i]){
            primes[cnt++] = i;
            s.insert(i);
        }
        for(int j = 0; j < cnt && primes[j] * i <= n; ++j){
            vis[primes[j]*i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int main(){
    init();
    int n;
    cin >> n;
    while (n--){
        int x;
        cin >> x;
        if (s.count(x)){
            cout << x <<" ";
        }
    }
    return 0;
}