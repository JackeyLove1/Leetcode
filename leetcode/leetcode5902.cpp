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


class Solution {
public:
    bool areNumbersAscending(string s) {
        istringstream str(s);
        string out;
        vector<string> strs;
        int cur = INT_MIN;
        while (str >> out) {
            try {
                int i = std::stoi(out);
                if (i > cur) {
                    cur = i;
                    continue;
                } else return false;
            }
            catch (std::exception const &e) {
                continue;
            }
        }
        return true;
    }
};