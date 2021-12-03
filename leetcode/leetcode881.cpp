#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int numRescueBoats(vector<int> &people, int limit) {
        sort(people.begin(), people.end());
        int l = 0, r = people.size() - 1;
        int res = 0;
        while (l < r) {
            if (l < r && people[l] + people[r] <= limit) {
                ++res, ++l, --r;
                if (l == r) {
                    ++res, --r;
                }
            } else {
                --r, ++res;
                if (l == r) {
                    ++res, --r;
                }
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {3, 2, 2, 1};
    auto s = Solution();
    cout << s.numRescueBoats(nums, 3) << " res: 3" << endl;
    vector<int> nums1 = {3, 5, 3, 4};
    cout << s.numRescueBoats(nums1, 5) << " res: 4" << endl;
    return 0;
}