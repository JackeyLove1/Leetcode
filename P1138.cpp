#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cstring>
#include <queue>
#include <random>

using namespace std;
constexpr int N = 1e4 + 100;
int n, k;

const int debug = 0;

inline void print(vector<int> &nums) {
    for_each(nums.begin(), nums.end(), [](int x) { cout << x << " "; });
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    vector<int> nums;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        nums.push_back(x);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    if (debug)print(nums);
    if (nums.size() < k) {
        cout << "NO RESULT" << endl;
        return 0;
    }
    cout << nums[k - 1] << endl;
    return 0;
}