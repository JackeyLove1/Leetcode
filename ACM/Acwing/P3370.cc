#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2, MOD = 1e9 + 7;

int main() {
    fhj();
    int m;
    cin >> m;
    std::unordered_set<std::string> us;
    us.reserve(m);
    string str;
    while (m--) {
        cin >> str;
        us.emplace(str);
    }
    cout << us.size() << endl;
    return 0;
}