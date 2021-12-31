#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool checkPerfectNumber(int num) {
        if(num == 1) return false;
        int sum = 1;
        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0){
                sum += i + num / i;
            }
        }
        return sum == num;
    }
};