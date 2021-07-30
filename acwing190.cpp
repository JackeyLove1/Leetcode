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

constexpr int N = 6;
int n;
string a[N], b[N];

inline int extend(queue<string> &q, unordered_map<string, int> &da, unordered_map<string, int> &db,
                  string a[], string b[]) {
    for (int k = 0, sk = q.size(); k < sk; k++) {
        string t = q.front();
        q.pop();

        for (int i = 0; i < t.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (t.substr(i, a[j].size()) == a[j]) {
                    string state = t.substr(0, i) + b[j] + t.substr(i + a[j].size());
                    if (da.count(state)) continue;
                    if (db.count(state)) return db[state] + 1 + da[t];
                    da[state] = da[t] + 1;
                    q.push(state);
                }
            }
        }
    }
    return 11;
}

inline int bfs(string A, string B) {
    queue<string> qa, qb;
    unordered_map<string, int> da, db;
    da[A] = 0, qa.push(A);
    db[B] = 0, qb.push(B);
    while (qa.size() && qb.size()) {
        int t;
        if (qa.size() <= qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b, a);
        if (t <= 10) return t;
    }
    return 11;
}

int main() {
    string A, B;
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n++;
    int step = bfs(A, B);
    if (step > 10) cout << "NO ANSWER!" << endl;
    else cout << step << endl;
    return 0;
}