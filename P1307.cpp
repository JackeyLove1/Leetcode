#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 10;
int n, m;

int main() {
    cin >> n;
    bool flag = n >= 0;
    n = abs(n);
    vector<int> nums;
    while (n) {
        nums.push_back(n % 10);
        n /= 10;
    }
    // reverse(nums.begin(), nums.end());
    while (!nums.empty() && nums.back() == 0) nums.pop_back();
    // print(nums);
    int res = 0;
    for (auto &num : nums) {
        res = res * 10 + num;
    }
    if (flag) cout << res << endl;
    else cout << -res << endl;
    return 0;
}