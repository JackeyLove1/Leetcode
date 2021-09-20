// Author: Jacky
// Time: 2021-09-19
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;


#include <sstream>

const int debug = 0;

inline vector<string> split(string &s) {
    istringstream str(s);
    string out;
    vector<string> res;
    if (s.empty()) return res;
    while (str >> out) {
        res.emplace_back(out);
    }
    if (debug) print(res);
    return res;
}

inline void record(vector<string> &strs, vector<vector<int>> &st) {
    for (auto &str : strs) {
        int x = stoi(str.substr(0, str.size() - 1));
        int y = str[str.size() - 1] - 'A';
        st[x][y] = 1;
        if (debug) cout << "x: " << x << " y: " << y << " res:" << st[x][y] << endl;
    }
}

inline int solve(vector<int> &state) {
    // judge 2
    bool success1 = true;
    for (int i = 1; i <= 8; ++i) {
        if (state[i]) {
            success1 = false;
            break;
        }
    }
    if (success1) return 2;
    bool success2 = true;
    for (int i = 1; i <= 4; ++i) {
        if (state[i]) {
            success2 = false;
            break;
        }
    }
    if (success2) return 1;
    bool success3 = true;
    for (int i = 3; i <= 6; ++i) {
        if (state[i]) {
            success3 = false;
            break;
        }
    }
    if (success3) return 1;
    bool success4 = true;
    for (int i = 5; i <= 8; ++i) {
        if (state[i]) {
            success4 = false;
            break;
        }
    }
    if (success4) return 1;
    return 0;
}

int solution(int N, string &S) {
    // write your code in C++14 (g++ 6.2.0)
    auto strs = std::move(split(S));
    vector<vector<int>> st(N + 5, vector<int>(12, 0));
    record(strs, st);
    int res = 0;
    for (int i = 1; i <= N; ++i) {
        res += solve(st[i]);
    }
    return res;
}

int main() {
    string s = "1A 2F 1C";
    cout << solution(2, s) << " res: 2" << endl;
    s = "";
    cout << solution(1, s) << " res: 2" << endl;
    return 0;
}