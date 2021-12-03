#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

char g[2][4];
unordered_map<string, pair<char, string>> pre;
unordered_map<string, int> dist;

inline void set(string state) {
    for (int i = 0; i < 4; i++) g[0][i] = state[i];
    for (int i = 7, j = 0; j < 4; i--, j++) g[1][j] = state[i];
}

inline string get() {
    string res;
    for (int i = 0; i < 4; i++) res += g[0][i];
    for (int i = 3; i >= 0; i--) res += g[1][i];
    return res;
}

inline string move0(string state) {
    set(state);
    for (int i = 0; i < 4; i++) swap(g[0][i], g[1][i]);
    return get();
}

inline string move1(string state) {
    set(state);
    int v0 = g[0][3], v1 = g[1][3];
    for (int i = 3; i >= 0; i--) {
        g[0][i] = g[0][i - 1];
        g[1][i] = g[1][i - 1];
    }
    g[0][0] = v0, g[1][0] = v1;
    return get();
}

inline string move2(string state) {
    set(state);
    int v = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = v;
    return get();
}

inline int bfs(string start, string end) {
    if (start == end) return 0;
    queue<string> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        auto t = q.front();
        int distance = dist[t];
        q.pop();

        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);
        for (int i = 0; i < 3; i++) {
            if (!dist.count(m[i])) {
                dist[m[i]] = distance + 1;
                pre[m[i]] = {'A' + i, t};
                q.push(m[i]);
                if (m[i] == end) return dist[m[i]];
            }
        }
    }
    return -1;
}

int main() {
    int x;
    string start, end;
    for (int i = 0; i < 8; i++) {
        cin >> x;
        end += char(x + '0');
    }
    for (int i = 1; i <= 8; i++) {
        start += char(i + '0');
    }

    int step = bfs(start, end);
    cout << step << endl;
    string res;
    while (end != start) {
        res += pre[end].first;
        end = pre[end].second;
    }
    reverse(res.begin(), res.end());
    if (step > 0) cout << res << endl;
    return 0;
}