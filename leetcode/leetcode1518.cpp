#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        // 简单的模拟题目
        int res = numBottles;
        int left = numBottles;
        while (left >= numExchange) {
            res += left / numExchange;
            left = left / numExchange + left % numExchange;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.numWaterBottles(15, 4) << " res: 19" << endl;
    cout << s.numWaterBottles(5, 5) << " res: 6" << endl;
}