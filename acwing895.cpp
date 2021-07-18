#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 100;
int a[N], f[N];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[i] = 1;
    }
    int res = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                f[i] = max(f[i], f[j] + 1);
                res = max(res, f[i]);
            }
        }
    }

    cout << res << endl;
    return 0;
}