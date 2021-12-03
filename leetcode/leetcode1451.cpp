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
    string arrangeWords(string text) {
        text[0] = tolower(text[0]);
        istringstream str(text);
        string out;
        vector<string> strs;
        while (str >> out) {
            strs.emplace_back(out);
        }
        stable_sort(strs.begin(), strs.end(), [&](const string &s1, const string &s2) {
            return s1.size() < s2.size();
        });
        string res;
        for (auto &s : strs) {
            res += s + " ";
        }
        res.pop_back();
        res[0] = toupper(res[0]);
        return res;
    }
};

int main() {
    auto s = Solution();
    auto strs = "Jlhvvd wfwnphmxoa qcuucx qsvqskq cqwfypww dyphntfz hkbwx xmwohi "
                "qvzegb ubogo sbdfmnyeim tuqppyipb llwzeug hrsaebveez aszqnvruhr xqpqd ipwbapd mlghuuwvec xpefyglstj dkvhhgecd kry";
    cout << s.arrangeWords(strs) << endl;
    return 0;
}