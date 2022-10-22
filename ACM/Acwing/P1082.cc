#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

int main() {
    fhj();
    int a, b, x = 0, y = 0;
    cin >> a >> b;
    int _ = exgcd(a, b, x, y);
    while (x <= 0){
        x += b;
    }
    cout << x << endl;
    return 0;
}