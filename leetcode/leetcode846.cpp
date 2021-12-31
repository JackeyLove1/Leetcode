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
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>
#include <tuple>
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
    bool isNStraightHand(vector<int> &hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;
        int sz = hand.size();
        int mod = sz / groupSize;
        sort(hand.begin(), hand.end());
        vector<vector<int>> cards(mod);
        for (const int num : hand) {
            int flag = false;
            for (int i = 0; i < mod; ++i) {
                if (cards[i].empty()) {
                    cards[i].push_back(num);
                    flag = true;
                    break;
                }
                if (!cards[i].empty() && cards[i].size() < groupSize && cards[i].back()+1 == num) {
                    cards[i].push_back(num);
                    flag = true;
                    break;
                }
            }
            if (!flag) return false;
        }
        return true;
    }
};

int main() {
    vector<int> hands = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    Solution s;
    cout << s.isNStraightHand(hands, 3) << " res: 1" << endl;
    vector<int> hands2 = {1, 2, 3, 4, 5};
    cout << s.isNStraightHand(hands2, 4) << " res: 0" << endl;
}