#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 510, M = 100010, INF = 1e8;

class Solution {
public:
    int maxScore(string s) {
        const int n = s.size();
        int zeros = 0, ones = 0;
        for(const auto ch : s){
            if (ch == '0') ++zeros;
            else ++ones;
        }
        int res = 0;
        int l = 0, r = ones;
        for(int i = 0; i < s.size() - 1; ++i){
            if (s[i] == '0'){
                ++l;
            }else{
                --r;
            }
            res = max(res, l + r);
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.maxScore("00111") << " res: 5" << endl;
    cout << s.maxScore("00") <<" res: 1" << endl;
    return 0;
}