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

constexpr int N = 550, M = 1e4, INF = 0x7fffffff;

class Solution {
public:
    const int debug = 1;
    vector<string> board = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};

    string alphabetBoardPath(string target) {
        using PII = pair<int, int>;
        unordered_map<char, PII> m;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                m[board[i][j]] = {i, j};
            }
        }
        string res = "";
        char start = 'a';
        for (int i = 0; i < target.size(); ++i) {
            if(target[i] == start){
                res.push_back('!');
                continue;
            }
            auto[x1, y1] = m[start];
            auto[x2, y2] = m[target[i]];
            if (start == 'z') {
                res.push_back('U');
                --x1;
            }
            if (target[i] == 'z') {
                --x2;
            }
            if (x1 < x2) {
                for (int j = x1; j < x2; ++j) {
                    res.push_back('D');
                }
            } else {
                for (int j = x1; j > x2; --j) {
                    res.push_back('U');
                }
            }
            if (y1 < y2) {
                for (int j = y1; j < y2; ++j) {
                    res.push_back('R');
                }
            } else {
                for (int j = y1; j > y2; --j) {
                    res.push_back('L');
                }
            }
            if (target[i] == 'z') {
                res.push_back('D');
            }
            res.push_back('!');
            if (debug) {
                cout << "st: " << start << " x1: " << x1 << " y1: " << y1 << endl;
                cout << "ta: " << target[i] << " x2: " << x2 << " y2: " << y2 << endl;
            }
            start = target[i];
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    // cout << s.alphabetBoardPath("leet") << endl;
    // cout << s.alphabetBoardPath("code") << endl;
    cout << s.alphabetBoardPath("zdz") << endl;
    return 0;
}