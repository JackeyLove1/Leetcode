#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;
static constexpr int N = 60;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int n;
using ll = long long;

int main() {
    fhj();
    vector<ll> a(N, 0), b(N, 0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    ll res1 = accumulate(a.begin(), a.begin() + n, 0);
    ll res2 = accumulate(b.begin(), b.begin() + n, 0);
    if (res1 >= res2) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}