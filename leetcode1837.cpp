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

constexpr int N = 550, M = 1e4, INF = 0x7fffffff;

class Solution {
public:
    int sumBase(int n, int k) {
        int sum = 0;
        while (n) {
            sum += n % k;
            n /= k;
        }
        return sum;
    }
};

int main() {
    auto s = Solution();
    cout << s.sumBase(34, 6) << endl;
    cout << s.sumBase(10, 10) << endl;
    return 0;
}