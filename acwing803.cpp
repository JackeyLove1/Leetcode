// 区间合并

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

using PII = pair<int, int>;

int main() {
    int n;
    cin >> n;
    vector<PII> v;
    int l, r;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
        v.emplace_back(l, r);
    }

    sort(v.begin(), v.end(), [](PII &p1, PII &p2) {
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    });

    vector<PII> res;
    int st = -2e9, ed = -2e9;
    for (auto &seg : v) {
        if (seg.first > ed) {
            if (ed != -2e9) res.emplace_back(st, ed);
            st = seg.first, ed = seg.second;
        } else {
            ed = max(ed, seg.second);
        }
    }
    if (st != -2e9) res.emplace_back(st, ed);
    cout << res.size() << endl;
    return 0;
}