#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <climits>

using namespace std;

int main() {
    using ll = long long;
    ll a, b, p;
    cin >> a >> b >> p;
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % p;
        b >>= 1;
        a = a * 2 % p;
    }

    cout << res << endl;
    return 0;
}