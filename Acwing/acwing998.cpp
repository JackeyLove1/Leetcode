// Author: Jacky
// Time: 2021-09-17
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


int n, m;
constexpr int N = 1e5 + 100;
const int debug = 0;
string op[N];
int t[N];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> op[i] >> t[i];
        if (debug)cout << op[i] << ' ' << t[i] << endl;
    }
    std::function<bool(bool, int)> cal = [&](bool num, int idx) -> int {
        if (debug) cout << "num: " << num;
        for (int i = 0; i < n; ++i) {
            if (op[i] == "AND") num &= (t[i] >> idx) & 1;
            else if (op[i] == "OR") num |= (t[i] >> idx) & 1;
            else num ^= (t[i] >> idx) & 1;
        }
        if (debug) cout << " idx: " << idx << " res: " << num << endl;
        return num;
    };
    int res = 0;
    for (int i = 29; i >= 0; --i) {
        if (m >> i) {
            int x = cal(0, i), y = cal(1, i);
            if (x >= y) res |= x << i;
            else res |= y << i, m -= 1 << i;
        } else {
            res |= (cal(0, i)) << i;
        }
        if (debug) cout << "after res: " << res << endl;
    }
    cout << res << endl;
    return 0;
}