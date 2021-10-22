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

constexpr int N = 22, M = 35, INF = 0x3f3f3f3f;

class Solution {
public:
    int diagonalSum(vector<vector<int>> &mat) {
        int n = mat.size();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += mat[i][i];
        }
        for (int i = n - 1, j = 0; j < n; --i, ++j) {
            sum += mat[i][j];
        }
        if (n & 1) {
            sum -= mat[n / 2][n / 2];
        }
        return sum;
    }
};
