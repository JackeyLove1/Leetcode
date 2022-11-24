#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int main() {
    int n;
    while (cin >> n && n) {
        struct node {
            string str;
            int mod;
        };
        queue<node> q;
        q.push(node{"1", 1});
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            if (t.mod == 0) {
                cout << t.str << endl;
                break;
            }
            q.push(node{t.str + "0", t.mod * 10 % n});
            q.push(node{t.str + "1", (t.mod * 10 + 1) % n});
        }
    }
    return 0;
}