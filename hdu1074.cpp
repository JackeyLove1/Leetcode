// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = (1 << 15) + 100, M = 1e4, INF = 0x7fffffff;

struct node {
    int ddl, cost;
    string name;
} q[N];

struct Node {
    int now, pre;
    int time = 0, result;
} f[N];

int n, m;
const int debug = 0;

inline void solve() {
    for (int i = 1; i <= m; ++i) {
        f[i].result = INF;
    }
    f[0].time = 0;
    f[0].result = 0;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(i & (1 << j))) {
                // add work j
                auto mark = i | (1 << j);
                auto time = f[i].time + q[j].cost;
                auto result = max(0, time - q[j].ddl); // deduct points
                result += f[i].result;
                if (f[mark].result > result) {
                    // state transition
                    f[mark].result = result;
                    f[mark].time = time;
                    f[mark].pre = i;
                    f[mark].now = j;
                }
                if (debug) {
                    cout << "mark: " << mark << " res: " << f[mark].result << endl;
                    cout << "time: " << time << " res: " << result << endl;
                }
            }
        }
    }
}

inline void output(int k) {
    if (k == 0) return;
    output(f[k].pre);
    cout << q[f[k].now].name << endl;
}

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        m = (1 << n) - 1;
        for (int i = 0; i < n; ++i) {
            cin >> q[i].name >> q[i].ddl >> q[i].cost;
        }
        solve();
        cout << f[m].result << endl;
        output(m);
    }
    return 0;
}