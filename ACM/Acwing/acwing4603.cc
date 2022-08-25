#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 100010;

int n, m;
int main(){
    fhj();
    cin >> m;
    while (m--){
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        int res = 0, cnt = 0;
        for (const auto ch : s){
            if (ch == 'A'){
                res = max(res, cnt);
                cnt = 0;
            }else {
                ++cnt;
            }
        }
        cout << res << endl;
    }
    return 0;
}