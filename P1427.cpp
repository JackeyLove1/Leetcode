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

constexpr int N = 20;

int main() {
    vector<int> nums;
    int n;
    while (cin >> n, n) {
        nums.push_back(n);
    }
    reverse(nums.begin(), nums.end());
    for (auto &num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}