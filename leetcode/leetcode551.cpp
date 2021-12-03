#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool checkRecord(string s) {
        int a = 0, l = 0;
        for (auto &ch : s) {
            if (ch == 'A') {
                if (++a >= 2) return false;
                l  = 0;
            } else if (ch == 'L') {
                if (++l >= 3) return false;
            } else {
                l = 0;
                continue;
            }
        }
        return true;
    }
};

int main() {

}