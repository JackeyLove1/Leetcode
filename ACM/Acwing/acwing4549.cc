#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100;
inline void fhj(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}
int main(){
    fhj();
    int n, s = 0, x;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> x;
        s = gcd(s, std::abs(x));
    }
    cout << s << endl;
    return 0;
}