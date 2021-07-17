#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 1e5 + 100;

using PII = pair<int, int>;
int n;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    vector<PII> v;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(a, b);
    }
    sort(v.begin(), v.end(), [](const PII &p1, const PII &p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        return p1.second < p2.second;
    });

    int ed = -2e9, res = 0;
    for (auto &p : v) {
        if (ed < p.first) {
            ed = p.second;
            res++;
            // cout << "ed: "<<ed<<endl;
        }
    }

    cout << res << endl;
    return 0;

}