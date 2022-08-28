#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 5510, INF = 1e9;

int main() {
    fhj();
    string s;
    cin >> s;
    if ((s.back() - '0') % 2) {
        cout << 1 << endl;
    }else {
        cout << 0 << endl;
    }
    return 0;
}