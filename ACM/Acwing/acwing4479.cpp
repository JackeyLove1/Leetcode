#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;

static constexpr int N = 1e5 + 100;
int a[N];
unordered_set<int> b;

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i){
        int x;
        cin >> x;
        b.insert(x);
    }
    for(int i = 0; i < n; ++i){
        if (b.count(a[i])){
            cout << a[i] <<" ";
        }
    }
    return 0;
}