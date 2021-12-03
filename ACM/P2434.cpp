#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 5e4 + 100, INF = 1e9;

int n, m;
using PII = pair<int, int>;
PII w[N];

int main() {
    fhj();
    cin >> n;
    int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        w[i] = {a, b};
    }
    sort(w, w + n, [](const PII &p1, const PII &p2) {
        return p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first;
    });
    auto[st, ed] = w[0];
    for (int i = 1; i < n; ++i) {
        if (w[i].first > ed) {
            cout << st << " " << ed << endl;
            st = w[i].first, ed = w[i].second;
        } else {
            ed = max(ed, w[i].second);
        }
    }
    cout << st << ' ' << ed << endl;
    return 0;
}