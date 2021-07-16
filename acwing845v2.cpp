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
    unordered_map<string, int> d;
    queue<string> q;
    string end = "12345678x";
    q.push(state);
    d[state] = 0;
    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        if (t == end) return d[t];

        int k = t.find('x');
        int x = k / 3, y = k % 3;
        int distance = d[t];
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                swap(t[a * 3 + b], t[k]);
                if (!d.count(t)) {
                    q.push(t);
                    d[t] = distance + 1;
                }
                swap(t[a * 3 + b], t[k]);
            }
        }
    }
    return -1;
}

int main() {
    string bg;
    char s[2];
    for (int i = 0; i < 9; i++) {
        cin >> s;
        bg += *s;
    }
    cout << bfs(bg) << endl;
    return 0;
}