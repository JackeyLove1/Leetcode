#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 6;
int n;
string A, B;
string a[N], b[N];
static std::hash<string> hs{};

int extend(queue<string> &q, unordered_map<size_t, int> &da, unordered_map<size_t, int> &db,
           string a[N], string b[N]) {
    int d = da[hs(q.front())];
    while (q.size() && da[hs(q.front())] == d) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < t.size(); j++)
                if (t.substr(j, a[i].size()) == a[i]) {
                    string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());
                    auto rs = hs(r);
                    if (db.count(rs)) return d + db[rs] + 1;
                    if (da.count(rs)) continue;
                    da[rs] = d + 1;
                    q.push(r);
                }
    }

    return 11;
}

int bfs() {
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<size_t, int> da, db;

    qa.push(A), qb.push(B);
    da[hs(A)] = db[hs(B)] = 0;

    int step = 0;
    while (qa.size() && qb.size()) {
        int t;
        if (qa.size() < qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b, a);

        if (t <= 10) return t;
        if (++step == 10) return -1;
    }

    return -1;
}

int main() {
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n++;

    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;

    return 0;
}