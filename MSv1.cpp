// Author: Jacky
// Time: 2021-09-19
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

int solution(int N, int K) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> nums;
    while (N) {
        nums.push_back(N % 10);
        N /= 10;
    }
    reverse(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        int diff = 9 - nums[i];
        if (K >= diff) {
            nums[i] = 9;
            K -= diff;
        } else {
            nums[i] += K;
            break;
        }
    }
    for (int i = 0; i < nums.size(); ++i) {
        res = res * 10 + nums[i];
    }
    return res;
}

int main() {
    cout << solution(512, 10) << " res: 972" << endl;
    cout << solution(191, 4) << " res: 591" << endl;
    return 0;
}