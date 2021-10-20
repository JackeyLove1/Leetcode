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

constexpr int N = 550, M = 1e4, INF = 0x7fffffff;

class Solution {
public:
    const int debug = 0;

    int getKth(int lo, int hi, int k) {
        unordered_map<int, int> m;
        m[2] = 1;
        m[3] = 7;
        std::function<int(int)> cal = [&](int x) -> int {
            if (m.count(x)) return m[x];
            m[x] = 0;
            int &v = m[x];
            if (x & 1) {
                v = cal(x * 3 + 1) + 1;
            } else {
                v = cal(x / 2) + 1;
            }
            return v;
        };
        vector<int> res;
        for (int i = lo; i <= hi; ++i) {
            res.push_back(i);
        }
        sort(res.begin(), res.end(), [&](int x, int y) {
            if (cal(x) == cal(y)) {
                return x < y;
            }
            return cal(x) < cal(y);
        });
        if (debug) {
            for (auto&[k, v] : m) {
                cout << "k: " << k << " v: " << v << endl;
            }
            print(res);
        }
        return res[k - 1];
    }
};

int main() {
    auto s = Solution();
    cout << s.getKth(12, 15, 2) << " res: 13" << endl;
    cout << s.getKth(10, 20, 5) << " res: 13" << endl;
    cout << s.getKth(1, 1000, 777) << " res: 570" << endl;
}