// 单向BFS法

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

int bfs(string state) {
    queue<string> q;
    unordered_map<string, int> d;
    d[state] = 0;
    q.push(state);

    int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};
    string end = "12345678x";
    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        if (t == end) return d[t];

        int distance = d[t];
        int k = t.find('x');
        int x = k / 3, y = k % 3;
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                swap(t[a * 3 + b], t[k]);
                if (!d.count(t)) {
                    d[t] = distance + 1;
                    q.push(t);
                    // cout << "t: "<< t << endl;
                }
                swap(t[a * 3 + b], t[k]);
            }
        }
    }
    return -1;
}

int main() {
    char s[2];
    string state;
    for (int i = 0; i < 9; i++) {
        cin >> s;
        state += *s;
    }
    // cout << state << endl;
    cout << bfs(state) << endl;
    return 0;
}