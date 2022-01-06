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
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}


class Solution {
public:
    string addSpaces(string s, vector<int> &spaces) {
        s = static_cast<const string>(s);
        unordered_set<int> us(spaces.begin(), spaces.end());
        string res;
        for (int i = 0; i < s.size(); ++i) {
            if (us.count(i)) res += " ";
            res += s[i];
        }
        return res;
    }
};
