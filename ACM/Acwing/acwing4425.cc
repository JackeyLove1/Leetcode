#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
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
constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f;

int main(){
    fhj();
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); ++i){
        if (i == 0 && s[i] == '9') {
            cout << s[i];
            continue;
        }
        if ('9' - s[i] < s[i] - '0') {
            cout << '9' - s[i];
        }else{
            cout << s[i];
        }
    }
    return 0;
}