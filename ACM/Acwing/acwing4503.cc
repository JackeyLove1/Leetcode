#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

int main() {
    fhj();
    int a, b, c;
    cin >> a >> b >> c;
    int res = 0;
    for(int i = 0; i <= a; ++i){
        for(int j = 0; j <= b; ++j){
            if (i + j == c){
                ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}