#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fhj();
    string s, t;
    cin >> s >> t;
    std::reverse(s.begin(), s.end());
    if (s.size() == t.size() && std::equal(s.begin(), s.end(), t.begin())) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}