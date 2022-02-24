#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

const int N = 101;
bool vis[N][N][N];

struct node {
    int s[3];
    int step;

    bool operator<(const node &rhs) const {
        return step > rhs.step;
    }
};

int hal, v[3];

inline bool match(const node &x) {
    int res = 0;
    for (int i : x.s) {
        if (i == hal) ++res;
    }
    return res == 2;
}

int bfs() {
    memset(vis, 0, sizeof vis);
    node st;
    st.s[0] = v[0], st.s[1] = 0, st.s[2] = 0;
    st.step = 0;
    priority_queue<node> q;
    q.push(st);
    vis[st.s[0]][0][0] = true;
    if (match(st)) return st.step;
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        for (int i = 0; i < 3; ++i) {
            if (t.s[i]) { // i -> j
                for (int j = 0; j < 3; ++j) {
                    if (j == i || t.s[j] == v[j]) continue;
                    // cout << "i: " << i << " j: " << j << endl;
                    auto cur = t;
                    if (cur.s[i] <= v[j] - cur.s[j]) {
                        cur.s[j] += cur.s[i];
                        cur.s[i] = 0;
                    } else {
                        cur.s[i] -= v[j] - cur.s[j];
                        cur.s[j] = v[j];
                    }
                    cur.step += 1;
                    if (match(cur)) return cur.step;
                    if (!vis[cur.s[0]][cur.s[1]][cur.s[2]]) {
                        vis[cur.s[0]][cur.s[1]][cur.s[2]] = true;
                        q.push(cur);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    fhj();
    while (cin >> v[0] >> v[1] >> v[2], v[0] || v[1] || v[2]) {
        if (v[0] & 1) {
            cout << "NO" << endl;
            continue;
        } else {
            hal = v[0] / 2;
            int res = bfs();
            if (res >= 0) cout << res << endl;
            cout << "NO" << endl;
        }
    }
    return 0;
}