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

using namespace std;

int n, sum;
const int debug = 0;

inline void print(vector<int> &nums) {
    for_each(nums.begin(), nums.end(), [](int x) { cout << x << " "; });
    cout << endl;
}

inline int solve(vector<int> &pre, vector<int> &vec) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += pre[i] * vec[i];
    }
    return s;
}

int main() {
    cin >> n >> sum;
    vector<int> vec = {1, 1};
    vector<int> pre;
    for (int i = 1; i <= n; ++i) {
        pre.push_back(i);
    }
    for (int i = 2; i < n; ++i) {
        vector<int> tmp;
        tmp.push_back(1);
        for (int j = 1; j < vec.size(); ++j) {
            tmp.push_back(vec[j - 1] + vec[j]);
        }
        tmp.push_back(1);
        vec = move(tmp);
    }
    if (debug) print(vec);
    do {
        auto s = solve(pre, vec);
        if (s == sum) {
            print(pre);
            break;
        }
    } while (next_permutation(pre.begin(), pre.end()));
    return 0;
}