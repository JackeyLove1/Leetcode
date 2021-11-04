#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>

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

constexpr int N = 110;
int n;

int main() {
    fhj();
    cin >> n;
    int x;
    vector<int> nums;
    // unordered_set<int> s;
    unordered_map<int, int> m;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        nums.push_back(x);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            ++m[nums[i] + nums[j]];
        }
    }
    int cnt = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.count(nums[i])) ++cnt;
    }
    cout << cnt << endl;
    return 0;
}