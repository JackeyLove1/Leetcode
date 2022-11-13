// practice 2022-11-12
// author: fanhj
#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
using ll = long long;
using PII = pair<int, int>;
const char colors[] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
bool found = false;
int res[110];
int n;

int main() {
    cin >> n;
    memset(res, -1, sizeof res);
    for (int i = 0; i < 7; ++i) {
        res[i] = i;
    }
    for (int i = 7; i <= n; ++i) {
        for (int k = 0; k < 7; ++k) {
            if (k != res[i - 1] && k != res[i - 2] && k != res[i - 3] && k != res[(i + 1) % n] &&
                k != res[(i + 2) % n] && k != res[(i + 3) % n]) {
                res[i] = k;
                break;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << colors[res[i]];
    }
    return 0;
}