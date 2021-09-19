// Author: Jacky
// Time: 2021-09-18
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

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

constexpr int N = 1e5 + 100;
double nums[N];
double s[N];
int n, F;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> F;
    double l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        r = max(nums[i], r);
    }

    std::function<bool(double)> check = [&](double avg) -> bool {
        for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + nums[i] - avg;
        double minv = 0.0;
        for (int i = 0, j = F; j <= n; ++i, ++j) {
            minv = min(minv, s[i]);
            if(s[j] - minv >= 0) return true;
        }
        return false;
    };

    while (r - l > 1e-5) {
        double mid = (r + l) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << int(1000 * r) << endl;
    return 0;
}