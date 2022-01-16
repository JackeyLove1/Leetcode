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

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::function<void(void)> check = [&]() {
        int a = nums[0] * 100 + nums[1] * 10 + nums[2];
        int b = nums[3] * 100 + nums[4] * 10 + nums[5];
        int c = nums[6] * 100 + nums[7] * 10 + nums[8];
        if (2 * a == b && 3 * a == c) {
            cout << a << " " << b << " " << c << endl;
        }
    };
    while (next_permutation(nums.begin(), nums.end())) {
        check();
    }
    return 0;
}