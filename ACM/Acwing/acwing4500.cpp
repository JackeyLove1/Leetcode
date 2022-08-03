#include <iostream>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using PII = pair<int, int>;

constexpr int N = 3300;
PII a[N];

int main() {
    fhj();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a[i] = {i, x};
    }
    sort(a, a + n, [](const PII &p1, const PII &p2) {
        return p1.second < p2.second;
    });
    int r1 = 0, r2 = -1, r3 = -1;
    for (int i = 0; i < n && r3 == -1; ++i) {
        cout << a[i].second << endl;
        if (r2 == -1 && a[i].second > a[r1].second) {
            r2 = i;
            continue;
        }
        if (r2 != -1  && a[i].second > a[r2].second) {
            r3 = i;
        }
    }

    if (r2 == -1 || r3 == -1) {
        cout << -1 << " " << -1 << " " << -1 << endl;
        return 0;
    }
    cout << r1 << " " << r2 << " " << r3 << endl;
    return 0;
}