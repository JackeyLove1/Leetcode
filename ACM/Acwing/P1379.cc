#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 10, l = 0, r = 9, dirs[]{3, -3, 1, -1};
int n;
string A, B{"123804765"};
static std::hash<string> hs{};

inline bool valid(int pos) {
    return l <= pos && pos <= r;
}

inline int extend(queue<string> &q, unordered_map<size_t, int> &da, unordered_map<size_t, int> &db) {
    int d = da[hs(q.front())];
    while (q.size() && da[hs(q.front())] == d) {
        auto t = q.front();
        q.pop();
        auto pos = t.find("0");
        for (auto dir: dirs) {
            auto pos_ = pos + dir;
            if (valid(pos_)) {
                auto tmp = t;
                std::swap(tmp[pos], tmp[pos_]);
                cout << tmp << endl;
                auto v = hs(tmp);
                if (db.count(v)) return da[hs(t)] + db[v] + 1;
                if (da.count(v)) continue;
                da[v] = da[hs(t)] + 1;
                q.push(tmp);
            }
        }
    }
    return 11;
}

int bfs() {
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<size_t, int> da, db;
    qa.push(A), qb.push(B);
    da[hs(A)] = db[hs(A)] = 0;
    int step = 0;
    while (qa.size() && qb.size()) {
        int t;
        if (qa.size() < qb.size()) t = extend(qa, da, db);
        else t = extend(qb, db, da);
        if (t <= 10) return t;
        if (++step == 10) return -1;
    }
    return -1;
}

int main() {
    cin >> A;
    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;
    return 0;
}