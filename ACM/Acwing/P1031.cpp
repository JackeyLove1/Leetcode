#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int N = 110;

int n, a[101], mid, all, ans;

int main() {
    fhj();
   cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], all += a[i];
    all /= n;
    for (int i = 1; i <= n; i++)
        if (a[i] - all)
            a[i + 1] += a[i] - all, ans++;
    cout << ans << endl;
    return 0;
}