#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static constexpr int N = 1e3 + 100;
int a[N];

int main() {
    fhj();
    int n;
    cin >> n;
    unordered_map<int, int> cnt;
    int kinds = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        kinds = max(kinds, cnt[a[i]]);
    }
    cout << kinds << endl;
    return 0;
}