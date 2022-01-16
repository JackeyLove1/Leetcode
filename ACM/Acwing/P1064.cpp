#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <climits>

using namespace std;

using PII = pair<int, int>;

const int N = 65, M = 32010;

int n, m;
PII master[N];
vector<PII> slave[N];
int f[M];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int v, w, q;
        cin >> v >> w >> q;
        w *= v;
        if (!q) master[i] = {v, w};
        else slave[q].emplace_back(v, w);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k < (1 << slave[i].size()); k++) {
                int v = master[i].first, w = master[i].second;
                for (int l = 0; l < slave[i].size(); l++) {
                    if (k & (1 << l)) {
                        v += slave[i][l].first;
                        w += slave[i][l].second;
                    }
                }
                if (j >= v) f[j] = max(f[j], f[j - v] + w);
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
