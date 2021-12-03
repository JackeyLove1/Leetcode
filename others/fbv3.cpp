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

static string s = "123456789";
using PII = pair<int, int>;
map<PII, bool> f;
int debug = 0;

bool solve(int cur, int val, int target, vector<string> &path) {
    bool b = false;
    if (cur == s.size() && val == target) {
        reverse(path.begin(), path.end());
        print(path);
        return true;
    }
    if (cur >= s.size()) return b;
    for (int len = 1; len + cur <= s.size(); ++len) {
        string sub = s.substr(cur, len);
        int v = stoi(sub);
        if (debug) cout << "v: " << v << endl;
        path.emplace_back(sub);
        path.emplace_back("+");
        b = b || solve(cur + len, val + v, target, path);
        path.pop_back();
        path.emplace_back("-");
        b = b || solve(cur + len, val - v, target, path);
        path.pop_back();
        path.pop_back();
    }
    return b;
}

int main() {
    vector<string> path;
    cout << solve(0, 0, 100, path) << endl;
    // cout << solve(0, 0, 1000, path) << endl;
}