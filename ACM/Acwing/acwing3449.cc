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
constexpr int N = 1e4 + 100, M = 1e5 + 100;

int n;

inline int check(int num){
    int  res = 0;
    while (num){
        res += num % 10;
        num /= 10;
    }
    return res;
}

int main() {
    fhj();
    string s;
    while (cin >> s && s != "0") {
        int num = 0;
        for(const auto ch : s){
            num += ch - '0';
        }
        while (num > 9){
            num = check(num);
        }
        cout << num << endl;
    }
    return 0;
}