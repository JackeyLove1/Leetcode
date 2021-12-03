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

constexpr int N = 1e6, M = 35, INF = 0x3f3f3f3f;

int a[7];
int f[N];

int main() {
    fhj();
    int step = 1;
    while (step) {
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            cin >> a[i];
            sum += a[i] * i;
        }
        if (sum == 0) break;
        cout << "Collection #" << step << ":" << endl;
        if (sum & 1) {
            cout << "Can't be divided." << endl << endl;
            step++;
            continue;
        }
        int target = sum / 2;
        vector<PII> goods; // v, w
        for (int i = 1; i <= 6; ++i) {
            if (!a[i]) continue;
            for (int k = 1; k <= a[i]; k <<= 1) {
                goods.emplace_back(k * i, k * i);
                a[i] -= k;
            }
            if (a[i]) {
                goods.emplace_back(a[i] * i, a[i] * i);
            }
        }
        for (auto &g : goods) {
            for (int j = target; j >= g.second; j--) {
                f[j] = max(f[j], f[j - g.second] + g.first);
            }
        }
        if (f[target] == target) {
            cout << "Can be divided." << endl;
        } else {
            cout << "Can't be divided." << endl;
        }
    }
}