#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

constexpr int N = 1e6 + 100, INF = 1e9;
using PII = pair<int, int>;
PII w[N];
int n;

int main() {
    fhj();
    cin >> n;
    int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        w[i] = {a, b};
    }
    sort(w, w + n, [](PII &p1, PII &p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        return p1.second < p2.second;
    });
    int res = 1;
    int ed = w[0].second;
    for (int i = 2; i < n; ++i) {
        if (w[i].first >= ed) {
            ed = w[i].second;
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}