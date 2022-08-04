#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 1005;
int n, m;

int main() {
    fhj();
    int a, b, c;
    cin >> a >> b >> c;
    if (a <= b && a <= c) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}