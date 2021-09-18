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
    cin >> n;
    vector<int> v;
    for (int i = 1; i <= n; ++i) {
        v.push_back(i);
    }
    do {
        print(v);
    } while (next_permutation(v.begin(), v.end()));
    return 0;
}