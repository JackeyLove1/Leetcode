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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;

    std::function<int(int)> cal = [](int num) -> int {
        int sum = 0;
        while (num) {
            sum += num & 1;
            num >>= 1;
        }
        return sum;
    };

    set<vector<int>> s;
    vector<int> tmp;
    for (int i = 0; i < (1 << n); ++i) {
        if (cal(i) != m) continue;
        tmp.clear();
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                tmp.push_back(j + 1);
            }
        }
        s.insert(tmp);
    }
    for (auto &vec : s) {
        for_each(vec.begin(), vec.end(), [](int x) { cout << x << " "; });
        cout << endl;
    }
    return 0;
}