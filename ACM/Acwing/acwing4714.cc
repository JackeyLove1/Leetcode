#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

using ll = __int128;

inline void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    fhj();
    string s;
    cin >> s;
    unordered_map<char, int> um;
    um.reserve(50);
    for (const auto c: s) {
        ++um[c];
    }
    ll res = 0;
    for (const auto c : s){
        res += 1;
        int left = um[c] > 1 ? um[c] - 1 : 0;
        res += left * 2;
        --um[c];
    }
    print(res);
    return 0;
}