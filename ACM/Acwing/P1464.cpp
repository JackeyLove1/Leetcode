// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2050;

using TIII = tuple<int, int, int>;
map<TIII, int> m;

int solve(int a, int b, int c) {
    auto p = make_tuple(a, b, c);
    if (m.count(p)) return m[p];
    int &v = m[p] = 0;
    if (a <= 0 || b <= 0 || c <= 0) return v = 1;
    if (a > 20 || b > 20 || c > 20) return v = solve(20, 20, 20);
    if (a < b && b < c) return v = solve(a, b, c - 1) + solve(a, b - 1, c - 1) - solve(a, b - 1, c);
    return v = solve(a - 1, b, c) + solve(a - 1, b - 1, c) + solve(a - 1, b, c - 1) - solve(a - 1, b - 1, c - 1);

}

int main() {
    fhj();
    int a, b, c;
    while (cin >> a >> b >> c && !(a == -1 && b == -1 && c == -1)) {
        printf("w(%d, %d, %d) = %d\n", a, b, c, solve(a, b, c));
    }
    return 0;
}